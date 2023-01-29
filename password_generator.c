#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void randomPasswordGeneration(char generated_password[],int N)
{
	int randomizer = 0;
	srand((unsigned int)(time(NULL)));

	char numbers[] = "0123456789";
	char letter[] = "abcdefghijklmnoqprstuvwyzx";
	char LETTER[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
	char symbols[] = "!@#$^&*?";

	randomizer = rand() % 4;

	for (int i = 0; i < N; i++) {

		if (randomizer == 1) {
			generated_password[i] = numbers[rand() % 10];
			randomizer = rand() % 4;
		}
		else if (randomizer == 2) {
			generated_password[i] = symbols[rand() % 8];
			randomizer = rand() % 4;
		}
		else if (randomizer == 3) {
			generated_password[i] = LETTER[rand() % 26];
			randomizer = rand() % 4;
		}
		else {
			generated_password[i] = letter[rand() % 26];
			randomizer = rand() % 4;
		}
	}
}

struct password
{
    char username[100];
    char site[100];
    char password[100];
};

struct user
{
    char login_username[100];
    char login_password[100];
};

int main()
{   
    int choice0;
    int choice1;
    int N;
    struct password pswd;
    struct user usr;
    char login_pass[100];
    char cont = 'y';
    FILE *fptr;

    system("clear");
    printf("\n\nPassword Generator and Viewer\n\n");
    printf("1.Login");
    printf("\n2.Register");
    printf("\n\nPlease enter your choice: ");
    scanf("%d",&choice0);

    switch (choice0)
    {
    case 1:
        system("clear");
        printf("\nEnter Login Username: ");
        scanf("%s",usr.login_username);
        fptr = fopen(strcat(usr.login_username,".bin"),"rb");
        
        if (fptr == NULL){
            printf("\nUser not registered\n");
        }
        else{
            printf("Enter password: ");
            scanf("%s",login_pass);
            fread(&usr,sizeof(struct user),1,fptr);
            fclose(fptr);

            if (!strcmp(login_pass,usr.login_password)){
                while (cont == 'y' || cont == 'Y'){
                    system("clear");
                    printf("\nWhat do you want to do?\n\n");
                    printf("1.Generate Password\n");
                    printf("2.View Passwords\n");
                    printf("\nPlease enter your choice: ");
                    scanf("%d",&choice1);

                    switch (choice1)
                    {
                    case 1:
                        system("clear");
                        printf("\nEnter Username: ");
                        scanf("%s",pswd.username);
                        printf("Enter site name: ");
                        scanf("%s",pswd.site);
                        printf("Enter the length of the password: ");
                        scanf("%d",&N);
                        randomPasswordGeneration(pswd.password,N);
                        printf("Generated Password: %s\n",pswd.password);
                        char filename[100];
                        strcpy(filename,usr.login_username);
                        strcat(filename,"_passwords");

                        fptr = fopen(strcat(filename,".bin"),"ab");
                        char content[3][1000];

                        fputs(pswd.username,fptr);
                        fputs("\n",fptr);
                        fputs(pswd.site,fptr);
                        fputs("\n",fptr);
                        fputs(pswd.password,fptr);
                        fputs("\n",fptr);
                        fclose(fptr);
                        break;

                    case 2:
                        system("clear");
                        char e_filename[100];
                        strcpy(e_filename,usr.login_username);
                        strcat(e_filename,"_passwords");
                        char e_content[3][1000];
                        int count = 1;
                        fptr = fopen(strcat(e_filename,".bin"),"rb");

                        if (fptr == NULL){
                            printf("\nNo passwords generated\n");
                        }
                        else{
                            while (fgets(e_content[0],1000,fptr)){
                                fgets(e_content[1],1000,fptr);
                                fgets(e_content[2],1000,fptr);
                                printf("%d. Username: %s   Site: %s   Password: %s\n",count,e_content[0],e_content[1],e_content[2]);
                                count+=1;
                            }
                            fclose(fptr);
                        }
                        break;

                    default:
                        printf("\nInvalid Input");
                        break;
                    }

                    printf("\nDo you want to continue(y/n)?: ");
                    scanf("%s",&cont);
                }
            }
            else{
                printf("Invalid Password\n");
            }

        }

        break;

    case 2:
        system("clear");
        printf("\n\nEnter New Credentials\n\n");
        printf("Enter Username: ");
        scanf("%s",usr.login_username);
        printf("Enter Password: ");
        scanf("%s",usr.login_password);
        fptr = fopen(strcat(usr.login_username,".bin"),"wb");
        fwrite(&usr,sizeof(usr),1,fptr);
        if (fwrite != 0){
            printf("\nSuccessfully Registered\n");
        }
        fclose(fptr);
        break;

    default:
        printf("\nInvalid Input");
        break;
    }

    printf("\n\nThank You\n");
	return 0;
}