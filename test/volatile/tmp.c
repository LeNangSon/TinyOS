void main(){
    char son = 'a';
    volatile char* son_locations = &son;
    while(*son_locations){
    }
}