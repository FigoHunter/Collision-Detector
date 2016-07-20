//
//  main.c
//  xxq
//
//  Created by 赵亦飞 on 16/7/13.
//  Copyright © 2016年 赵亦飞. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
struct collider{
    struct collider *preCollider;
    int collision[3];
    struct collider *postCollider;
};
struct colliderPool{
    struct collider *head;
    struct collider *tail;
    int size;
    };

void collisionTrigger(struct collider* collider1, struct collider* collider2);

static struct colliderPool cp;
struct collider *addElement(int posX,int posY, int diameter);
void removeElement(struct collider *collider);

void initColliderPool()
{
    cp.head=NULL;
    cp.tail=NULL;
    cp.size=0;
}

struct collider * createCollider(int posX,int posY, int diameter)
{
    return addElement(posX,posY, diameter);
}

void destroyCollider(struct collider *collider)
{
    removeElement(collider);
}

void moveCollider(int x, int y,struct collider* collider)
{
    if(collider!=NULL)
    {
        collider->collision[0]+=x;
        collider->collision[1]+=y;
    }
    else{
        printf("collider to move not exist\n");
    }
}

struct collider *addElement(int posX,int posY, int diameter)
{
    struct collider *temp=(struct collider*)malloc(sizeof(struct collider));
    temp->collision[0]=posX;
    temp->collision[1]=posY;
    temp->collision[2]=diameter;
    if(cp.head==NULL)
    {
        temp->preCollider=NULL;
        temp->postCollider=NULL;
        cp.head=temp;
        cp.tail=temp;
    }
    else
    {
        cp.tail->postCollider=temp;
        temp->preCollider=cp.tail;
        temp->postCollider=NULL;
        cp.tail=temp;
    }
    cp.size++;
    return cp.tail;
}

void removeElement(struct collider *collider)
{
    if(collider!=NULL)
    {
    if(collider==cp.tail)
    {
        collider->preCollider->postCollider=NULL;
        cp.tail=collider->preCollider;
        free(collider);
    }
    else if (collider==cp.head)
    {
        collider->postCollider->preCollider=NULL;
        cp.head=collider->postCollider;
        free(collider);
    }
    else{
        collider->preCollider->postCollider=collider->postCollider;
        collider->postCollider->preCollider=collider->preCollider;
        free(collider);
    }
    cp.size--;
    }
    else{
        printf("Collider to destroy not exists\n");
    }
}

void collisionDetection(struct collider *collider1,struct collider *collider2)
{
    int gapX = abs(collider1->collision[0]-collider2->collision[0]);
    int gapY = abs(collider1->collision[1]-collider2->collision[1]);
    int xStandard;
    int yStandard;
    if(collider1->collision[0]<collider2->collision[0])
    {
        xStandard=collider1->collision[2];
    }
    else
    {
        xStandard=collider2->collision[2];
    }
    if(collider1->collision[1]<collider2->collision[1])
    {
        yStandard=collider1->collision[2];
    }
    else
    {
        yStandard=collider2->collision[2];
    }
    if(gapX<=xStandard&&gapY<=yStandard)
    {
        collisionTrigger(collider1, collider2);
    }
}

void collisionDetectionLoop()
{
    struct collider *temp1=cp.head;
    struct collider *temp2=cp.head;
    for(int i=0; i<cp.size;i++)
    {
        for(int j=0;j<i;j++)
        {
            collisionDetection(temp1, temp2);
            temp2=temp2->postCollider;
        }
        temp1=temp1->postCollider;
        temp2=cp.head;
    }
}

void collisionTrigger(struct collider* collider1, struct collider* collider2)
{
    printf("%d %d %d and %d %d %d has collided\n",collider1->collision[0],collider1->collision[1],collider1->collision[2],collider2->collision[0],collider2->collision[1],collider2->collision[2]);
}

int main(int argc, const char * argv[]) {
    initColliderPool();
    // insert code here...
    struct collider *temp;
    struct collider *afdb;
    struct collider *haha;
    temp=createCollider(1, 2,3);
    createCollider(3, 4,4);
    createCollider(7, 8,6);
    afdb=createCollider(9, 10,7);
    createCollider(11, 12,8);
    createCollider(5, 6,5);
    haha=createCollider(13, 14,2);
    destroyCollider(temp);
    destroyCollider(haha);
    destroyCollider(afdb);
    struct collider *tem;
    tem = cp.head;
    for (int i=0; i<cp.size; i++) {
        printf("%d %d %d\n",tem->collision[0],tem->collision[1],tem->collision[2]);
        tem=tem->postCollider;
    }
    printf("%d %d %d %d\n",temp->collision[0],temp->collision[1],temp->collision[2],cp.size);
    collisionDetectionLoop();
    return 0;
}
