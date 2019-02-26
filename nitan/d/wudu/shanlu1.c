#include <ansi.h>
inherit ROOM;

string look_bei();

void create()
{
        set("short", "山邊小路");
        set("long", @LONG
一條蜿蜒的小路延着山腳向前延伸，兩旁是濃密的樹林，腳下是
崎嶇不平的山路，前面就是可怕的黑森林了。旁邊似乎有一家山野小
店，路邊有一座石碑(bei)。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "south" : __DIR__"milin1",
                "west" : __DIR__"xiaodian",
                "north" : __DIR__"road3",
        ]));

        set("item_desc",([
                "bei" : (: look_bei :),
        ]));

        setup();
}

string look_bei()
{
    return
    "\n"
              WHT "          ####################################\n"
                  "          ####                            ####\n"
                  "          ####        前方黑森林山高林    ####\n"
                  "          ####    密，百里之內不見人煙    ####\n"  
                  "          ####    有虎狼出沒其中，行人    ####\n"  
                  "          ####    請三思而後行！          ####\n"  
                  "          ####                            ####\n"  
                  "          ####################################\n\n" NOR;
    "\n";
}