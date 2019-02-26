// Room: /d/baihuagu/tree.c 樹林
// Last Modified by Winder on Mar. 5 2001
inherit ROOM;
void create()
{
        set("short", "樹林");
        set("long", @LONG
叢林中一片黑暗，你瞪大眼睛，覺得到處都是路，又好像到處
都不是路。若是在叢林中迷失了方向，這輩子就別想活着走出去了。
LONG);
        set("outdoors", "baihuagu");
        set("exits", ([ 
                "north": __DIR__"treen",  
                "west" : __DIR__"treew",
                "south": __DIR__"trees",
                "out"  : __DIR__"ent",
                "east" : __DIR__"treee",
        ]));
        set("coor/x", -450);
        set("coor/y", -400);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_go","go");
}
int do_go()
{
        if( random(40)<(query("kar", this_player())) )
        {
                this_player()->move(__DIR__"tree1");
                return 1;
        }
        else
                if(random(5))
                {
                        this_player()->move(this_object());
                        return 1;
                }
}