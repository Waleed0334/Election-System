#include<stdio.h>
void votes(int c1, int c2,int c3,int c4){
    printf("Candidate A achived %d votes\n",c1);
    printf("Candidate B achived %d votes\n",c2);
    printf("Candidate C achived %d votes\n",c3);
    printf("Candidate D achived %d votes\n",c4);
    printf("---------------------------------------------------------\n");

}

int winner(int c1, int c2,int c3,int c4 ){
    if (c1 > c2 && c1 > c3 && c1 > c4)
        {
            votes(c1,c2,c3,c4);//function call
            printf("The winner is Candidate A\n");
        }
    else if (c2 > c1 && c2 > c3 && c2 > c4)
        {
            votes(c1,c2,c3,c4);//function call
            printf("The winner is Candidate B\n");
        }
    else if (c3 > c1 && c3 > c2 && c3 > c4)
        {
            votes(c1,c2,c3,c4);//function call
            printf("The winner is Candidate C\n");
        }
    else if (c4 > c1 && c4 > c2 && c4 > c3)
    {
        votes(c1,c2,c3,c4);//function call
        printf("The winner is Candidate D\n");
    }
    return 0;
}

int voterTable(char name[][20], int id[], int total_user) {
    for (int i = 0; i < total_user; i++)
    {
        printf(" %d . %s  |  ID: %d \n", i+1, name[i], id[i]);
        printf("---------------------------------------------------------\n");
    }
    return 0;
}


int main(){
    char name[100][20];
    int id[100];
    int userID=0, exit;n
    int choice = 0;
    int c1=0,c2=0,c3=0,c4=0;
    int total_user=0;
    for (int i = 0; i < 100; i++)
    {
        printf("=============Welcome To the voting platform=============\n");
        printf("-------------------------------------------------------------\n");
        printf("Enter your name:\n ");
        scanf("%s", name[i]);

        printf("Enter your id: ");
        scanf("%d", & userID);

        if ( userID > 100 ||  userID <= 0)
        {
            printf("No ID record found\n");
            continue;
        }

        if (i==0)
        {
            id[i] = userID;
        }else{
            for (int j = 0; j < 100; j++)
            {
                if (id[j]==userID)
                {
                    printf("already exist!\n");
                    return 0;
                }  
            }
            id[i]=userID;
        }

        total_user++;
        
        printf("Select your candidate\n");
        printf("-------------------------------------------------------------\n");
        printf("Press 1 for Candidate A\n");
        printf("Press 2 for Candidate B\n");
        printf("Press 3 for Candidate C\n");
        printf("Press 4 for Candidate D\n");
        printf("-------------------------------------------------------------\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: 
                c1++;
                printf("Thank you for voting Candidate A\n");
                break;
            case 2: 
                c2++; 
                printf("Thank you for voting Candidate B\n");
                break;
            case 3: 
                c3++; 
                printf("Thank you for voting Candidate C\n");
                break;
            case 4: 
                c4++; 
                printf("Thank you for voting Candidate D\n");
                break;
            default: 
                printf("Invalid choice!\n"); 
                break;
        }

        printf("Press 0 to exit or any key to continue: ");
        scanf("%d", &exit);
        if(exit == 0) {
            break;
        }
    }

    printf("\n=======Election Result:=======\n");
    printf("---------------------------------------------------------\n");
    printf("in this election %d users participates\n",total_user);
    printf("---------------------------------------------------------\n");
    
    winner(c1,c2,c3,c4);//function call
    printf("---------------------------------------------------------\n");

    printf("======Voter's ID Table======\n");

    voterTable(name, id, total_user);//function call

    return 0;
}