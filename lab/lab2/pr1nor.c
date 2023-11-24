#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define max 100
int N;// Record the quantity entered
int inorder[max]={0},preorder[max]={0},postorder[max]={0};// Use three arrays to store the data input by the three traversal methods
int reinorder[max]={0},repreorder[max]={0},repostorder[max]={0};// Use three arrays to create data filled by three traversal methods
int reinorder1[max]={0},repreorder1[max]={0},repostorder1[max]={0};
int rec[120]={0};// Used to record the number of occurrences of each number
int lose=0,losecopy,losenum;// It is used to record the number of figures that never appear, refresh the number in recursion, and record which figures never appear
int relevelorder[max][max];// Record the reconstructed sequence traversal with two-dimensional array
int floorarry[max];// Used to record the number of elements contained in each layer in sequence traversal
int maxfloor=0;// Used to record the maximum number of layers in sequence traversal

void cinData();
int rem();
int examinationleft(int top1,int top2,int top3,int length);
int examinationright(int top1,int top2,int top3,int length);
void BuildTree(int top1,int front1,int top2,int front2,int floor);
void coutData();// Output four traversal results after filling
int examinationcopy(int top1,int top2,int top3,int length);
int main()
{
    cinData();// input data
    int t;
    t=rem();// Preliminary check whether more than two or more digits are lost. If yes, return 0
    if (t==0)//If 0 is returned, output "Impossible"
    {
        printf("Impossible");
        return 0;
    }
    int m,n;
    m=examinationleft(0,0,0,N);// Put the three sorts into the function to check whether they meet the conditions for unique tree construction from left to right. If they cannot be constructed, 0 will be returned
    n=examinationright(0,0,0,N);//Put the three sorts into the function to check whether they meet the conditions for unique tree construction from right to left. If they cannot be constructed, 0 will be returned
    int only=0;
    for(int i=0;i<N;i++)//check if the tree is unique 
    {
        if(reinorder[i]!=reinorder1[i]||repreorder[i]!=repreorder[i]||repostorder[i]!=repostorder[i])
            only=1;
    }
    if (m==0||only==1)//If 0 is returned, output "Impossible"
    {
        printf("Impossible");
        return 0;
    }
    coutData();// The three sequences after filling and the sequence traversal output of structures
    return 0;
}

/*
The Function Name:cinData
*
Function:Enter data and record the number of occurrences of each number
*
Usage:Direct Call
*/
void cinData()
{
    scanf("%d",&N);// Number of input elements
    for(int i=0;i<N;i++) 
    {   
        scanf("%d",&inorder[i]);// Here, according to the cast, if '-' appears, the number 0 will be automatically entered in the array
        rec[inorder[i]]++;// For each occurrence of the input number, the corresponding number position in the rec array+1
    }
    for(int i=0;i<N;i++) 
    {   
        scanf("%d",&preorder[i]);// Here, according to the cast, if '-' appears, the number 0 will be automatically entered in the array
        rec[preorder[i]]++;// For each occurrence of the input number, the corresponding number position in the rec array+1
    }
    for(int i=0;i<N;i++) 
    {   
        scanf("%d",&postorder[i]);// Here, according to the cast, if '-' appears, the number 0 will be automatically entered in the array
        rec[postorder[i]]++;// For each occurrence of the input number, the corresponding number position in the rec array+1
    }
}

/*
The Function Name:rem
*
Function:Judge whether two or more figures do not appear
*
Usage:Direct Call
*/

int rem()//Judge whether two or more digits do not appear
{
    for(int i=1;i<=N;i++)
    {
        if (rec [i]==0)//If the number at the corresponding position in the rec array is 0, it means that the number never appears
        {
            lose++;// Number of never occurring numbers+1
            losenum=i;// Losenum is only used to record a number that does not appear, because if two or more numbers appear, the positions of these numbers can be changed at will, and the generated tree must not be unique
        }
    }   
    losecopy=lose;// The number of copies of lose. It is used in subsequent recursion. If the number of times of lose has been used up, but the condition is not found, the original value of lose should be restored in the next case
    if (lose>=2)//If two or more numbers appear, the positions of these numbers can be changed at will. The tree generated must not be unique. If not, 0 is returned
    {
        return 0;
    }
    else
        return 1;
}
/*
The Function Name:examination
*
Function:Check whether the uniquely generated tree can be generated from left to right
*
Usage:Direct Call
*
top1:the head of inorder traversal
*
top2:the head of preorder traversal
*
top3:the head of postorder traversal
*
length:the length of the tree
*/
int examinationleft (int top1, int top2, int top3, int length)//The first three are the interval headers of three orders, and the length is the interval length
{
    if (length==0)//If the interval length is 0, it means that the tree is empty, which must be true
        return 1;
    for (int l1=0; l1<=length-1; l1++)//Both the preamble and the preamble have clear root node location characteristics, so it is necessary to assume from beginning to end whether the location of the root node in the middle order traversal conforms to
    {
        lose=losecopy;// Restore the value of lose
        int l2=length-l1-1;// Rooted in inorder [l1+top1]
        int num1=0,num2=0;// Num1 is used to record the types of numbers that appear at the three root node locations, and num2 is used to record the number of times the same number appears at the three root node locations
        int thisnum;// Used to determine the value of the root node under this assumption
        if(inorder[top1+l1]>0)
        {
            num1++;// If the assumed root position is a number, since it is the first time, the number type is directly+1
            num2++;// Similarly, the number of occurrences of the same number +1
            thisnum=inorder[top1+l1];// Record the number of the current root node
        }
        if(preorder[top2]>0&&preorder[top2]!=inorder[top1+l1])
            num1++;// If the root node position of the first order traversal is a number, but it is different from the middle order traversal, then the number type+1
        if(preorder[top2]>0)
        {
            num2++;// If the position of the first order traversal root node is a number, the number of occurrences of the number+1
            thisnum=preorder[top2];// Update the number of roots
        }
        if(postorder[top3+length-1]>0&&postorder[top3+length-1]!=inorder[top1+l1]&&postorder[top3+length-1]!=preorder[top2])
            num1++;// If the root node position of subsequent traversal is a number, but it is different from that of intermediate and prior traversal, then the number type+1
        if(postorder[top3+length-1]>0)
        {
            num2++;// If the root node position of subsequent traversal is a number, the number of occurrences of the number+1
            thisnum=postorder[top3+length-1];// Update the number of roots
        }
        if (num1>=2)//If the number type is greater than or equal to 2, it indicates that there is a conflict. Try the next one directly
            continue;
        if (num1==0)//If there are no numbers in the root node positions of the three traversals, consider that there may be Losenumber
        {
            if (lose==0)//If there is no Losenumber, it indicates that there is a conflict. Try the next one directly
                continue;
            if (lose==1)//If there is exactly one Losenumber, consider that the number of the root node is Losenumber
            {
                reinorder[top1+l1]=losenum;// Fill the losenumber into the root node of the reconstructed array
                repreorder[top2]=losenum;
                repostorder[top3+length-1]=losenum;
                lose--;// At the same time, after filling, there will be no figures that do not appear
            }
        }
        if (num1==1)//If the number type is exactly, you need to further check
        {
            if (num2!=rec [thisnum])
                continue;
            else
            {
                reinorder[top1+l1]=thisnum;// If it also matches, fill the number in the corresponding position of the reconstruction array
                repreorder[top2]=thisnum;
                repostorder[top3+length-1]=thisnum;
            }
        }
        int x1=examinationleft(top1,top2+1,top3,l1);// If the above conditions are met, the system will recursively enter the left subtree to continue checking. If the left subtree also meets the conditions, 1 will be returned
        int x2=examinationleft(top1+l1+1,top2+l1+1,top3+l1,l2);// If all the above conditions are met, the system will recursively enter the right subtree and continue to check. If the right subtree is also met, 1 will be returned
        if (x1==1&&x2==1)//If both sides return 1, it is considered that this is true, and the entire function returns 1
            return 1;
}
}
/*
The Function Name:examination
*
Function:Check whether the uniquely generated tree can be generated from right to left
*
Usage:Direct Call
*
top1:the head of inorder traversal
*
top2:the head of preorder traversal
*
top3:the head of postorder traversal
*
length:the length of the tree
*/
int examinationright (int top1, int top2, int top3, int length)//The first three are the interval headers of three orders, and the length is the interval length
{
    if (length==0)//If the interval length is 0, it means that the tree is empty, which must be true
        return 1;
    for (int l1=length-1; l1>=0; l1--)//Both the preamble and the preamble have clear root node location characteristics, so it is necessary to assume from beginning to end whether the location of the root node in the middle order traversal conforms to
    {
        lose=losecopy;// Restore the value of lose
        int l2=length-l1-1;// Rooted in inorder [l1+top1]
        int num1=0,num2=0;// Num1 is used to record the types of numbers that appear at the three root node locations, and num2 is used to record the number of times the same number appears at the three root node locations
        int thisnum;// Used to determine the value of the root node under this assumption
        if(inorder[top1+l1]>0)
        {
            num1++;// If the assumed root position is a number, since it is the first time, the number type is directly+1
            num2++;// Similarly, the number of occurrences of the same number +1
            thisnum=inorder[top1+l1];// Record the number of the current root node
        }
        if(preorder[top2]>0&&preorder[top2]!=inorder[top1+l1])
            num1++;// If the root node position of the first order traversal is a number, but it is different from the middle order traversal, then the number type+1
        if(preorder[top2]>0)
        {
            num2++;// If the position of the first order traversal root node is a number, the number of occurrences of the number+1
            thisnum=preorder[top2];// Update the number of roots
        }
        if(postorder[top3+length-1]>0&&postorder[top3+length-1]!=inorder[top1+l1]&&postorder[top3+length-1]!=preorder[top2])
            num1++;// If the root node position of subsequent traversal is a number, but it is different from that of intermediate and prior traversal, then the number type+1
        if(postorder[top3+length-1]>0)
        {
            num2++;// If the root node position of subsequent traversal is a number, the number of occurrences of the number+1
            thisnum=postorder[top3+length-1];// Update the number of roots
        }
        if (num1>=2)//If the number type is greater than or equal to 2, it indicates that there is a conflict. Try the next one directly
            continue;
        if (num1==0)//If there are no numbers in the root node positions of the three traversals, consider that there may be Losenumber
        {
            if (lose==0)//If there is no Losenumber, it indicates that there is a conflict. Try the next one directly
                continue;
            if (lose==1)//If there is exactly one Losenumber, consider that the number of the root node is Losenumber
            {
                reinorder1[top1+l1]=losenum;// Fill the losenumber into the root node of the reconstructed array
                repreorder1[top2]=losenum;
                repostorder1[top3+length-1]=losenum;
                lose--;// At the same time, after filling, there will be no figures that do not appear
            }
        }
        if (num1==1)//If the number type is exactly, you need to further check
        {
            if (num2!=rec [thisnum])
                continue;
            else
            {
                reinorder1[top1+l1]=thisnum;// If it also matches, fill the number in the corresponding position of the reconstruction array
                repreorder1[top2]=thisnum;
                repostorder1[top3+length-1]=thisnum;
            }
        }
        int x1=examinationright(top1,top2+1,top3,l1);// If the above conditions are met, the system will recursively enter the left subtree to continue checking. If the left subtree also meets the conditions, 1 will be returned
        int x2=examinationright(top1+l1+1,top2+l1+1,top3+l1,l2);// If all the above conditions are met, the system will recursively enter the right subtree and continue to check. If the right subtree is also met, 1 will be returned
        if (x1==1&&x2==1)//If both sides return 1, it is considered that this is true, and the entire function returns 1
            return 1;
}
}
/*
The Function Name:BuildTree
*
Function:Two dimensional array of sequence traversal constructed by inorder traversal and postorder traversal
*
Usage:Direct Call
*
top1:the head of inorder traversal
*
front1:the tail of preorder traversal
*
top2:the head of postorder traversal
*
front2:the tail of postorder traversal
*
floor:the floor of sequence traversal
*/
void BuildTree(int top1,int front1,int top2,int front2,int floor)
{
    int root;// Find the position of the root node in the middle order traversal
    if (top1>front1 || top2>front2)//Judge whether it is empty
        return;// If null, the function will be terminated directly
    for (int i=top1; i<=front1; i++)//Find the number of the root  inorder traversal through the postorder traversal
    {
        if (reinorder [i]==repostorder [front2])//The number is the same as the end
        {
            root=i;
            break;
        }
    }
    if (floor>=maxfloor)//If the number of layers is greater than the maximum number of layers recorded
        maxfloor=floor;// Update the maximum number of layers to the current number of layers
    floorarry[floor]++;// Add one to the number of data contained in this layer
    relevelorder[floor][floorarry[floor]]=repostorder[front2];// Fill the root node into the reconstructed sequence traversal
    BuildTree(top1,root-1,top2,top2+root-top1-1,floor+1);// Recursion to left subtree
    BuildTree(root+1,front1,front2+root-front1,front2-1,floor+1);// Recursion to right subtree
}


/*
The Function Name:coutData
*
Function:Print the three sorts that are rebuilt and sequence traversal
*
Usage:Direct Call
*/
void coutData()
{
    for (int i=0; i<N; i++)//Output the reconstructed medium order traversal in order
    {
        if(i==0)
            printf("%d",reinorder[0]);// The first number is output specially
        else
            printf(" %d",reinorder[i]);
    }
    printf("\n");// Wrap lines before outputting the next sequence
    for (int i=0; i<N; i++)//Output the first traversal after reconstruction in order
    {
        if(i==0)
            printf("%d",repreorder[0]);// The first number is output specially
        else
            printf(" %d",repreorder[i]);
    }
    printf("\n");// Wrap lines before outputting the next sequence
    for (int i=0; i<N; i++)//Output the post reconstruction traversal in order
    {
        if(i==0)
            printf("%d",repostorder[0]);// The first number is output specially
        else
            printf(" %d",repostorder[i]);
    }
    printf("\n");
    BuildTree(0,N-1,0,N-1,0);// Establish sequence traversal array
    for (int i=0; i<=maxfloor; i++)//Cycle the two-dimensional array of sequence traversal from layer 0 to the maximum layer
    {
        if(i==0)
            printf("%d",relevelorder[0][1]);// The first number is output specially
        else
        {   
            for (int j=1; j<=floorarry [i]; j++)//Output the number of layer i circularly from 1 to the maximum number of elements
                printf(" %d",relevelorder[i][j]);
        }
    }
}