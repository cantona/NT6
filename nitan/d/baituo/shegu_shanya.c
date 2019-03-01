// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蛇谷山崖");
        set("long", @LONG
這是蛇谷高處的斷崖，周遭既無樹木，也無雜草，一派荒涼景象，
唯有風聲獵獵，不斷從耳邊呼嘯而過。居高臨下，極目而望，可以遠
眺(view)四面八方，看盡山巒形勢。
LONG );

        set("exits", ([ 
            "southdown" : __DIR__"shegu19",
        ]));

        set("objects", ([
            __DIR__"npc/tuying" : 2,
        ]));

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49940);
        set("coor/y", 20200);
        set("coor/z", 30);
        setup();
}

void init()
{
        add_action("do_view","view");
        add_action("do_view","tiaowang");
}

int do_view(string arg)
{
        object me = this_player(), room;
        string msg;

        if( !arg || arg=="" ) 
                return notify_fail( "你要往哪個方向眺望？可以從平面八個方位中選擇。\n");

        switch (arg) {
        case "north" :
        case "n" :
        msg = "你往北方遠眺，盡是一片崇山峻嶺。\n";
                break;

        case "south" :
        case "s" :
        msg = "你往南方遠眺，蛇谷地勢盡在眼前，可以遙遙望見谷口。\n";

        room = load_object(__DIR__"shegu1");
        if( query("defense", room) )
        msg += RED"谷口彌漫著血紅色的毒霧，與外隔絕。\n"NOR;
        else msg += HIW"原本紅霧密布的谷口，這時卻豁然開朗，所有的霧氣都無影無蹤了。\n"NOR;
                break;

        case "east" :
        case "e" :
        msg = "你往東方遠眺，在越過一片胡楊林後，便是黃沙莽莽的大漠。\n";
                break;

        case "west" :
        case "w" :
        msg = "你往西方遠眺，所見盡是蛇谷林木。\n";
                break;

        case "northeast" :
        case "ne" :
        msg = "你往東北遠眺，盡是一片崇山峻嶺。\n";
                break;

        case "northwest" :
        case "nw" :
        msg = "你往西北遠眺，望見遠方山溝間雲杉茂密，白楊參天，一座大瀑布奔騰而下，景象壯觀。\n";

        room = load_object(__DIR__"shegu27");
        if( present("dang gui", room) ) 
        msg += HIW"一眼望去，你覺得彼端山中，似有股難以描述的靈氣。\n"NOR;
        else if( present("pusiqu she", room) ) 
        msg += HIR"你遙望山中景色，忽然覺得有些心驚肉跳，再定神望去，越看越覺得不對勁。\n"NOR;
        else msg += "你悠閒地觀賞著山景，覺得心情輕鬆了不少。\n";
                break;

        case "southeast" :
        case "se" :
        msg = "你往東南遠眺，在越過一片胡楊林後，便是黃沙莽莽的大漠。\n";
                break;

        case "southwest" :
        case "sw" :
        write("你往西南遠眺，正可望見蛇谷密林深處的□魔鬼灘□地帶……\n\n");
        room = load_object(__DIR__"shegu32");
        COMMAND_DIR"std/look"->look_room(me, room);
        msg = "……距離雖遠，但是居高臨下，倒還看得清楚。\n";
                break;

        default:
                return notify_fail( "你要往哪個方向眺望？可以從平面八個方位中選擇。\n");
        }
        write(msg);
        return 1;
}