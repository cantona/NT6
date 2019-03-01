//  Room:  /d/lanzhou/caoyuan3.c

inherit  ROOM;

void  create  ()
{
        int dir1,dir2,dir3,dir4;
        dir1=random(5)+1;
        dir2=random(5)+1;
        dir3=random(5)+1;
        dir4=random(5)+1;
        while (dir1!=4 && dir2!=4 && dir3!=4 && dir4!=4)        
        {        
                dir1=random(5)+1;
                dir2=random(5)+1;
                dir3=random(5)+1;                
                dir4=random(5)+1;                
        }
        set("short",  "大草原");
        set("long",  @LONG
西北平原上的大草原，較之蒙古草原毫不遜色。綠油油的牧草直連
天邊。西北的藍天綠地，比起東北的黑山白水來，別有一番風趣。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south" : __DIR__"caoyuan"+dir1,
                "north" : __DIR__"caoyuan"+dir2,
                "east"  : __DIR__"caoyuan"+dir3,
                "west"  : __DIR__"caoyuan"+dir4,
        ]));
        set("objects",  ([
                "/d/xingxiu/npc/herdsman" : random(2),
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15740);
	set("coor/y", 3790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}