#include<stdio.h>
#include<string.h>

//function to hashed the given string
char *hashedString(char *text,int length){
    char url_array[150];
    static char hashed_array[150];
    int y,i,x;
    int text_length = strlen(text);
    url_array[0]=50+text_length;
    //get the string of length 24/132
    for(i=0;i<=((length-1)/text_length);i++){
        for(y=0;y<=(text_length-1);y++){
            x = (text_length*i)+y+1;                
            if(x>=length){ 
                break;
            }else{
                url_array[x]=text[y]+i;
            } 
        }  
    }
    //hashed the url_array 
    for(int z=0;z<=(length-1);z++){
        if(z<=text_length){
            hashed_array[z]=url_array[z];
        }else{
            hashed_array[z]=url_array[length-(z-text_length)];
        }
    }
    return hashed_array;
}

//function to convert given number to binary representation of 9 bits
int *binary_array(int num){
    static int binaryNum[9];
    for(int i=8;i>=0;i--){
        binaryNum[i] = num%2;
        num = num/2;
    }
    return binaryNum;
}

//print a small square in given colour
void clr_sq(int clr_Num){
    if(clr_Num==1){        
        printf("\033[0;40m  \033[0m"); 
    }else if(clr_Num==2){  
        printf("\033[0;41m  \033[0m");   
    }else if(clr_Num==3){  
        printf("\033[0;42m  \033[0m");
    }else if(clr_Num==4){
        printf("\033[0;43m  \033[0m");
    }else if(clr_Num==5){  
        printf("\033[0;44m  \033[0m"); 
    }else if(clr_Num==6){  
        printf("\033[0;45m  \033[0m");
    }else {                
        printf("\033[0;46m  \033[0m");
    }          
}

void white(){                        //print a white colour small square
    printf("\033[0;47m  \033[0m");
}

//function to move the cursor position 
void move_up(int position){
   printf("\x1b[%dA",position);
}
void move_down(int position){
   printf("\x1b[%dB",position);
}
void move_right(int position){
   printf("\x1b[%dC",position);
}
void move_left(int position){
   printf("\x1b[%dD",position);
}
void move_to(int row,int col){
    printf("\x1b[%d;%df",row,col);    
}

//function that encoded a one character into a given colour
void encode_char(int binaryNum[9],int clr_Num){
    for(int i=0;i<3;i++){       
        for(int j=0;j<3;j++){
            int count=(3*i)+j; 
            if(binaryNum[count]==1){
                clr_sq(clr_Num);
            }else{
                white();   
            }  
        }      
        move_down(1);
        move_left(6);
    }
}

//function that print the position identification square in given colour
void position_sq(int clr_Num){
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            if((i*j)==0||((i*j)%5)==0){
                clr_sq(clr_Num);
            }else if((i==2||i==3)&&(j==2||j==3)){
                clr_sq(clr_Num);               
            }else {  
                white();
            }
        }
        move_down(1);
        move_left(12);
    } 
}

//function to print the background
void background(char version){
    if(version=='S'){    
        for(int i=0;i<20;i++){
            for(int j=0;j<20;j++){
                white();  
            }
            move_down(1);
            move_left(40);
        }  
    }else{
        for(int i=0;i<38;i++){
            for(int j=0;j<38;j++){
                white();  
            }
            move_down(1);
            move_left(76);
        }
    }
}

//function that initiate the printing of QRcode
void set_terminal(int clr_Num,char version){
    printf("\x1b[2J");
    move_to(0,0);
    background(version);
    move_to(2,3);
    position_sq(clr_Num);
    move_right(12);  
}

//printing the small QRcode of 24 elements, part by part
void part1_Scode(char *text,int clr_Num){   //print first 16 elements
    int element=0;
    for(int i1=0;i1<4;i1++){
        for(int j1=0;j1<4;j1++){                
            encode_char(binary_array(text[element]),clr_Num);   
            move_right(6);
            move_up(3); 
            element++;  
        } 
        move_left(24);
        move_down(3);
    }     
}
void part2_Scode(char *text,int clr_Num){  //print next 4 elements
    move_up(18);
    int element=16;
    for(int i2=0;i2<2;i2++){
        for(int j2=0;j2<2;j2++){            
            encode_char(binary_array(text[element]),clr_Num);
            move_right(6);
            move_up(3); 
            element++;  
        }
        move_left(12);
        move_down(3);
    }
    move_right(12);
    move_up(6);
    position_sq(clr_Num);     
}
void part3_Scode(char *text,int clr_Num){   //print last 4 elements
    move_left(24);
    int element=20;
    for(int i3=0;i3<2;i3++){
        for(int j3=0;j3<2;j3++){            
            encode_char(binary_array(text[element]),clr_Num);
            move_right(6);
            move_up(3);
            element++;   
        }
        move_left(12);
        move_down(3);
    }
    position_sq(clr_Num);
    printf("\n");
}
//print the small QRcode
void small_QRcode(char *text,int clr_Num){
    set_terminal(clr_Num,'S');
    part1_Scode(text,clr_Num);
    part2_Scode(text,clr_Num);    
    part3_Scode(text,clr_Num);
}

//printing the large QRcode of 132 elements, part by part
void part1_Lcode(char *text,int clr_Num,int text_len){//print first 100 elements
    int element=0;
    for(int i1=0;i1<10;i1++){
        for(int j1=0;j1<10;j1++){
            if(element==0){
                if(text_len>=78){
                    encode_char(binary_array(50+text_len),clr_Num);
                }else{
                    encode_char(binary_array(text[0]),clr_Num); 
                } 
            }else{  
                encode_char(binary_array(text[element]),clr_Num);  
            } 
            move_right(6);
            move_up(3);
            element++; 
        }    
        move_left(60);
        move_down(3);
    }  
}
void part2_Lcode(char *text,int clr_Num){  //print next 16 elements
    move_up(36);
    int element=100;
    for(int i2=0;i2<2;i2++){
        for(int j2=0;j2<8;j2++){
            encode_char(binary_array(text[element]),clr_Num);
            move_right(6);
            move_up(3);  
            element++;       
        }
        move_left(48);
        move_down(3);
    }
    move_right(48);
    move_up(6);
    position_sq(clr_Num);
}
void part3_Lcode(char *text,int clr_Num){  //print last 16 elements
    move_left(60);
    int element=116;
    for(int i3=0;i3<8;i3++){
        for(int j3=0;j3<2;j3++){
            encode_char(binary_array(text[element]),clr_Num);
            move_right(6);
            move_up(3);
            element++;   
        }
        move_left(12);
        move_down(3);
    }
    position_sq(clr_Num);
    printf("\n");
}
//print the large QRcode
void large_QRcode(char *text,int clr_Num,int text_len){
    set_terminal(clr_Num,'L');
    part1_Lcode(text,clr_Num,text_len);
    part2_Lcode(text,clr_Num);    
    part3_Lcode(text,clr_Num);
}

//function that print the error message
void error_msg(char *argument){
  printf("usage :\n");
  printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argument); 
  printf("%s -h for the help about the program\n",argument); 
}


int main(int argc,char* argv[]){
        
    int colour=0;
    //declaring the variables for arguments 
    char h[10]={'-','h'},c[10]={'-','c'};   
    char black[10]={'b','l','a','c','k'},BLACK[10]={'B','L','A','C','K'};
    char red[10]={'r','e','d'},RED[10]={'R','E','D'};
    char green[10]={'g','r','e','e','n'},GREEN[10]={'G','R','E','E','N'};
    char yellow[10]={'y','e','l','l','o','w'},
         YELLOW[10]={'Y','E','L','L','O','W'};
    char blue[10]={'b','l','u','e'},BLUE[10]={'B','L','U','E'};
    char mag[10]={'m','a','g','e','n','t','a'},
         MAG[10]={'M','A','G','E','N','T','A'};
    char cyan[10]={'c','y','a','n'},CYAN[10]={'C','Y','A','N'};

 
    //one argument is given
    if(argc==1){              
        colour=1;  
    //two arguments are given
    }else if(argc==2){        
        if(strcmp(h,argv[1])==0){                     
            error_msg(argv[0]);            
        }else{
            printf("Incorrect usage of arguments.\n");
            error_msg(argv[0]);             
        }
    //three arguments are given
    }else if(argc==3){        
        if(strcmp(c,argv[1])==0){  
        //if argument -c given find colour that need to print the QR           
            if((strcmp(black,argv[2])==0)||(strcmp(BLACK,argv[2])==0)){
                colour=1;
            }else if((strcmp(red,argv[2])==0)||(strcmp(RED,argv[2])==0)){
                colour=2; 
            }else if((strcmp(green,argv[2])==0)||(strcmp(GREEN,argv[2])==0)){
                colour=3;   
            }else if((strcmp(yellow,argv[2])==0)||(strcmp(YELLOW,argv[2])==0)){
                colour=4;
            }else if((strcmp(blue,argv[2])==0)||(strcmp(BLUE,argv[2])==0)){
                colour=5;
            }else if((strcmp(mag,argv[2])==0)||(strcmp(MAG,argv[2])==0)){
                colour=6;
            }else if((strcmp(cyan,argv[2])==0)||(strcmp(CYAN,argv[2])==0)){
                colour=7;
            }else{
                printf("Invalid argument for color.\n");
                error_msg(argv[0]);
            }
        }else{
            printf("Incorrect usage of arguments.\n");
            error_msg(argv[0]); 
        }
    //more than three arguments are given
    }else{                   
        printf("Incorrect usage of arguments.\n");
        error_msg(argv[0]);    
    }  
    
    if(colour!=0){
        char url_text[500];
        printf("Enter the URL: ");
        scanf("%s",url_text);
        int url_length;
        url_length = strlen(url_text);

        if(url_length<=3){
            printf(
"String is too short. Not supported by available QR versions\n");
        }else if(url_length<=20){
            small_QRcode(hashedString(url_text,24),colour);
            //printf("%s",hashedString(url_text,24)); 
            printf("\n"); 
        }else if(url_length<120){
            large_QRcode(hashedString(url_text,132),colour,url_length);
            //printf("%s",hashedString(url_text,132));   
            printf("\n");  
        }else{
            printf(
"String is too long. Not supported by available QR versions\n");  
        } 

    }else{
    }
    
    return 0;

}  



