/* Your code here! */
#include "maze.h"
/*
* Empty Constructor
*/
SquareMaze::SquareMaze(){
}

/*
* Sets up a maze and randomizes walls by setting right_wall and down_wall to be false
*/
void SquareMaze::makeMaze(int width, int height){
    this->width = width;
    this->height = height;
    this->size = width*height;
    DisjointSets maze;
    maze.addelements(size);

    for (int i=0;i<size;i++){
        //mark every cell to have walls
        r_wall.push_back(true);
        d_wall.push_back(true);
    }

    //push all the walls in the walls map excluding the edges
    for (int x=0;x<width;x++){
        for (int y=0;y<height;y++){
            if (x<width-1){
                pair<int,int> cell (x,y);
                pair<pair<int,int>,int> right_wall(cell,0);
                walls.push_back(right_wall);
            }
            if (y<height-1){
                pair<int,int> cell (x,y);
                pair<pair<int,int>,int> left_wall(cell,1);
                walls.push_back(left_wall);
            }
        }
    }

    //randomize the order of the walls
    random_shuffle(walls.begin(),walls.end());

    //iterate through all the walls
    for (unsigned i=0;i<walls.size();i++){
        pair<int,int> cell = walls[i].first;
        pair<int,int> query;
        int dir = walls[i].second;

        if (dir == 0){ // find right neighbor
            query.first = cell.first+1;
            query.second = cell.second;
        }
        else{
            query.first = cell.first;
            query.second = cell.second+1;
        }

        if (maze.find(cell.second*width+cell.first)!=maze.find(query.second*width+query.first)){
            setWall(cell.first,cell.second,dir,0);
            maze.setunion(cell.second*width+cell.first,query.second*width+query.first);
        }
    }

}

/*
* Checks whether a given cell (x,y) can move the given dir
*/
bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (x>-1 && x<width && y>-1 && y<height){
        if (dir == 0 && x+1<width){
            return !r_wall[y*height+x];
        }
        else if (dir == 1 && y+1<height){
            return !d_wall[y*height+x];
        }
        else if (dir == 2 && x-1 > -1){
            return !r_wall[y*height+(x-1)];
        }
        else if (dir == 3 && y-1 > -1){
            return !d_wall[(y-1)*height+x];
        }
    }
    return false;
}
/*
* Sets up the wall on the cell (x,y) depending on the exists variable
*/
void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if (y<height-1 && dir == 1)
        d_wall[y*height+x] = exists;
    if (x<width-1 && dir == 0)
        r_wall[y*height+x] = exists;
}

/*
* Uses DFS to solve the maze. Will get the longest path to the entry point
*/
vector<int> SquareMaze::solveMaze(){
    unordered_map<int, int> dict;
    queue<int> q;
    bool ** visited = new bool*[width];
    for (int i=0;i<width;i++){
        visited[i] = new bool[height];
    }
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            visited[i][j] = false;
        }
    }
    visited[0][0] = true;
    q.push(0);

    while (!q.empty()) {
        int curr_cell = q.front();
        int curr_x = curr_cell%width;
        int curr_y = curr_cell/width;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int next_x,next_y;
            if (i == 0) {
                next_x = curr_x+1;
                next_y = curr_y;
            }
            else if (i == 1){
                next_x = curr_x;
                next_y = curr_y+1;
            }
            else if (i == 2){
                next_x = curr_x-1;
                next_y = curr_y;
            }
            else{
                next_x = curr_x;
                next_y = curr_y-1;
            }


            if (canTravel(curr_x,curr_y,i) && !visited[next_x][next_y]) {
                dict[next_y*width+next_x] = curr_cell;
                q.push(next_y*width+next_x);
                visited[next_x][next_y] = true;

            }
        }
    }

    vector <int> compare; // actual path
    int max = 0;
    int max_end = 0;
    for (int i = 0; i <width; i++){
        int start = (height-1)*width +i;
        int end = 0;
        int count = 0;

        while (end!=start){
            start = dict[start];
            count++;
        }

        if (count > max){
            max = count;
            max_end = i;
        }
    }
    int start = (height-1)*width+max_end;
    while (start!=0){ // if the endpoint reaches the startpoint break
        int next = dict[start];
        if (start-1 == next){
            compare.insert(compare.begin(),0);
        }
        else if (start+1 == next){
            compare.insert(compare.begin(),2);
        }
        else if (start-width == next){
            compare.insert(compare.begin(),1);
        }
        else if (start+width == next){
            compare.insert(compare.begin(),3);
        }
        start = next;
    }

    for (int j=0;j<height;j++){
        delete visited[j];
    }
    delete [] visited;
    return compare;
}

/*
* Draws, but does not solve the actual maze. It will draw based on a x10 scale on the PNG
*/
PNG* SquareMaze::drawMaze() const {
    PNG* maze = new PNG(width * 10 + 1, height * 10 + 1);
    for (unsigned i=0; i<maze->height(); i++){
        HSLAPixel* pixel = &(maze->getPixel(0,i));
        pixel->h = 0;
        pixel->s = 0;
        pixel->l = 0;
        pixel->a = 1;
    }
    for (unsigned i=10; i<maze->width(); i++){
        HSLAPixel* pixel = &(maze->getPixel(i,0));
        pixel->h = 0;
        pixel->s = 0;
        pixel->l = 0;
        pixel->a = 1;
    }
    for (int x = 0; x<width; x++){
        for (int y = 0; y<height; y++){
            if (r_wall[y*height+x]){
                for (int cell = 0;cell<11;cell++){
                    HSLAPixel *pixel = &(maze->getPixel((x + 1) * 10, y * 10 + cell));
                    pixel->h = 0;
                    pixel->s = 0;
                    pixel->l = 0;
                    pixel->a = 1;
                }
            }

            if (d_wall[y*height+x]){
                for (int cell = 0;cell<11; cell++){
                    HSLAPixel* pixel = &(maze->getPixel(x*10+cell,(y+1)* 10));
                    pixel->h = 0;
                    pixel->s = 0;
                    pixel->l = 0;
                    pixel->a = 1;
                }
            }
        }
    }
    return maze;
}

/*
* Will draw the vector path in red on the actual image of the PNG
*/
PNG* SquareMaze::drawMazeWithSolution(){
    PNG* solution = drawMaze();
    vector<int> path_solution = solveMaze();

    int x=5, y=5;
    for (unsigned i=0;i<path_solution.size();i++){
        if (path_solution[i] == 0){
            for (int offset = 0; offset < 11; offset++){
                HSLAPixel *pixel = &(solution->getPixel(x+offset, y));
                pixel->h = 0;
                pixel->s = 1;
                pixel->l = 0.5;
                pixel->a = 1;
            }
            x += 10;
        }
        else if (path_solution[i] == 1){
            for (int offset = 0; offset < 11; offset++){
                HSLAPixel *pixel = &(solution->getPixel(x, y + offset));
                pixel->h = 0;
                pixel->s = 1;
                pixel->l = 0.5;
                pixel->a = 1;
            }
            y += 10;
        }
        else if (path_solution[i] == 2){
            for (int offset = 0; offset < 11; offset++){
                HSLAPixel *pixel = &(solution->getPixel(x - offset, y));
                pixel->h = 0;
                pixel->s = 1;
                pixel->l = 0.5;
                pixel->a = 1;
            }
            x -= 10;
        }
        else {
            for (int offset = 0; offset < 11; offset++){
                HSLAPixel *pixel = &(solution->getPixel(x, y - offset));
                pixel->h = 0;
                pixel->s = 1;
                pixel->l = 0.5;
                pixel->a = 1;
            }
            y -= 10;
        }
    }

    x = x / 10;
    y = height - 1;
    for (int offset = 1; offset < 10; offset++) {
        HSLAPixel *pixel = &(solution->getPixel(x * 10 + offset, (y + 1) * 10));
        pixel->h = 0;
        pixel->s = 0;
        pixel->l = 1;
        pixel->a = 1;
    }

    return solution;
}

/*
* Creates a maze that is the shape of an Illini I block
*/
PNG* SquareMaze::drawCreativeMaze(){
    for (int x=0;x<width;x++){
        if (x<15 || x>width-15){
            d_wall[14*width+x] = true;
            d_wall[(height-15-1)*width+x] = true;
        }
    }
    for (int y=15;y<height-15;y++){
        r_wall[y*width+14]=true;
        r_wall[y*width+(width-15-1)] = true;
    }

    int new_w = width*10+1;
    int new_h = height*10+1;
    PNG * creative_image = new PNG(new_w, new_h);
    int top_y = 15*10;
    int bottom_y = new_h-(15*10);
    int left_x = 15*10;
    int right_x = new_w-(15*10);

    for (int y=0;y<new_h;y++){
        if (y<top_y || y>bottom_y){
            HSLAPixel* pixel = &(creative_image->getPixel(0,y));
            pixel->h = 0;
            pixel->s = 0;
            pixel->l = 0;
            pixel->a = 1;
        }
        else{
            HSLAPixel* pixel1 = &(creative_image->getPixel(left_x,y));
            HSLAPixel* pixel2= &(creative_image->getPixel(right_x,y));
            pixel1->h = 0;
            pixel2->h = 0;
            pixel1->s = 0;
            pixel2->s = 0;
            pixel1->l = 0;
            pixel2->l = 0;
            pixel1->a = 1;
            pixel2->a = 1;
        }
    }

    for (int x=10;x<new_w;x++){
        HSLAPixel* pixel = &(creative_image->getPixel(x,0));
        pixel->h = 0;
        pixel->s = 0;
        pixel->l = 0;
        pixel->a = 1;
    }

    for (int x=0;x<new_w;x++){
        if (x<=left_x || x>=right_x){
            HSLAPixel* pixel = &(creative_image->getPixel(x,bottom_y));
            pixel->h = 0;
            pixel->s = 0;
            pixel->l = 0;
            pixel->a = 1;
        }
    }

    for (int x=0;x<width;x++){
        for (int y=0;y<height;y++){
            if (y<height-15&& y>=15){
                if (x<width-15&&x>=15){
                    if (d_wall[y*width+x]){
                        for (int k=0;k<=10;k++){
                            HSLAPixel* pixel = &(creative_image->getPixel(x*10+k,(y+1)*10));
                            pixel->h = 0;
                            pixel->s = 0;
                            pixel->l = 0;
                            pixel->a = 1;
                        }
                    }
                    if (r_wall[y*width+x]){
                        for (int k=0;k<=10;k++){
                            HSLAPixel* pixel = &(creative_image->getPixel((x+1)*10,y*10+k));
                            pixel->h = 0;
                            pixel->s = 0;
                            pixel->l = 0;
                            pixel->a = 1;
                        }
                    }
                }
            }
            else{
                if (d_wall[y*width+x]){
                    for (int k=0;k<=10;k++){
                        HSLAPixel* pixel = &(creative_image->getPixel(x*10+k,(y+1)*10));
                        pixel->h = 0;
                        pixel->s = 0;
                        pixel->l = 0;
                        pixel->a = 1;
                    }
                }
                if (r_wall[y*width+x]){
                    for (int k=0;k<=10;k++){
                        HSLAPixel* pixel = &(creative_image->getPixel((x+1)*10,y*10+k));
                        pixel->h = 0;
                        pixel->s = 0;
                        pixel->l = 0;
                        pixel->a = 1;
                    }
                }
            }
        }
    }
    return creative_image;
}
