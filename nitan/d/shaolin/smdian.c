#include <ansi.h> 
inherit ROOM;

void init();
void close_gate();
int do_close(string arg);
string look_gate();
int do_open(string arg);

void create()
{
        set("short", "山門殿");
        set("long", @LONG
這裏便是少林寺的前殿山門殿了。只見殿內青磚鋪地，兩側分列
哼、哈二將。身軀雄偉，面相忿怒，頭帶寶冠，上半身裸露，手執金
剛杵，一鼓鼻，一張口，露牙睜目，兇猛可畏。兩邊各放一紅木供桌，
陳列香燭，以供僧俗叩拜。自此的左右各有一間偏殿，供比丘們打坐
誦經之用。南面是一道三丈來高的硃紅杉木包銅大門(gate)。
LONG );
        set("exits", ([
                "east" : __DIR__"smdian1",
                "west" : __DIR__"smdian2",
                "north" : __DIR__"taijie",
        ]));
        set("item_desc",([
                "gate" : (: look_gate :),
        ]));
        set("objects",([
                __DIR__"npc/seng-bing3" : 2,
                __DIR__"npc/xiang-ke" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_open", "open");
        add_action("do_close", "close");
}

void close_gate()
{
        object room;

        if(!( room = find_object(__DIR__"guangchang1")) )
                room = load_object(__DIR__"guangchang1");
        if(objectp(room))
        {
                delete("exits/south");
                        message("vision", HIY "僧兵上前把大門關了起來。\n" NOR,
                                          this_object());
                delete("exits/north", room);
                message("vision", HIY "只聽乒地一聲，裏面有人把大門關上了。\n"
                                  NOR, room);
        }
}

int do_close(string arg)
{
        if (!query("exits/south"))
                return notify_fail("大門已經是關着的了。\n");

        if (!arg || (arg != "gate" && arg != "south"))
                return notify_fail("你要關什麼？\n");

        message_vision(CYN "$N" CYN "朝着僧兵點了點頭。\n" NOR, this_player());

        remove_call_out("close_gate");
        call_out("close_gate", 2);

        return 1;
}

int do_open(string arg)
{
        object room;

        if (query("exits/south"))
                return notify_fail("大門已經是開着了。\n");

        if (!arg || (arg != "gate" && arg != "south"))
                return notify_fail("你要開什麼？\n");

        if(!( room = find_object(__DIR__"guangchang1")) )
                room = load_object(__DIR__"guangchang1");
        if(objectp(room))
        {
                set("exits/south", __DIR__"guangchang1");
                message_vision(HIY "$N" HIY "使勁把大門打了開來。\n" NOR, this_player());
                set("exits/north", __FILE__, room);
                message("vision", HIY "只聽吱地一聲，裏面有人把大門打開了。\n" NOR, room);
                remove_call_out("close_gate");
                call_out("close_gate", 10);
        }

        return 1;
}

string look_gate()
{
        return YEL "一道三丈來高的硃紅杉木包銅大門。\n" NOR;
}

int valid_leave(object me, string dir)
{
        if( query("id", me) == "sengbing" && dir == "south")return 0;

        return ::valid_leave(me, dir);
}
