#include <ansi.h> 
inherit ROOM;

string* npcs = ({
        "/clone/worm/xixuezhu",
        "/clone/worm/renmianzhu",
        "/clone/worm/tianwu",
        "/clone/worm/jiuweixie",
        "/clone/worm/shishixie",
        "/clone/worm/tieguxie",
        "/clone/worm/heiguafu",
        "/clone/worm/jinxianwugong",
});

void create()
{
        set("short", RED "萬毒窟" NOR);
        set("long", @LONG
這裏是山洞內部的支洞，這裏已經沒有一絲光線了，黑洞洞的什
麼也看不見。洞內巖壁(wall)上好像生着幾株不知名的小草。身旁傳
來一陣“噝噝”的聲音。
LONG);
        set("item_desc", ([
                "wall" : WHT "一堵巖壁，上面突出些石筍，似乎可以順着爬上去。\n" NOR,
        ]));
        set("exits", ([
                "north" : __DIR__"wandu2",
        ]));

        set("objects", ([
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
        ]));
    

        setup();
}

void init()
{
       add_action("do_climb", "climb");
}
int do_climb(string arg)
{
       
        object me = this_player();
        object ob; 

        if( (!arg) ||!((arg == "wall") || (arg == "巖壁")))
                return notify_fail("你要爬什麼？\n");

        message_vision(HIC "$N" HIC "攀着巖壁上突出的石筍艱難的爬了上去。\n\n" NOR,me);
        ob = load_object(__DIR__"dongxue");
        ob = find_object(__DIR__"dongxue");
        message("vision",HIC+query("name", me)+HIC"從下面爬了上來。\n"NOR,ob);

        me->move(__DIR__"dongxue");
        return 1;
}
