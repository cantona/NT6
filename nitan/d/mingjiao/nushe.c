// Room: /d/mingjiao/nushe.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

string look_dui();

void create()
{
        set("short", "地門女舍");
        set("long", @LONG
走進這間女舍，一陣脂粉淡香撲面，似有似無，似茉莉，似丁香，
似玫瑰，似夜來香，讓人心神盪漾。幾位姑娘斜倚闌窗，吟詩作畫，
全不似武林中人，誰能想到，她們都是叱吒江湖的巾幗女傑呢？
LONG );
        set("exits", ([
                "out" : __DIR__"mjdimen1",
        ]));
        set("item_desc",(["dui lian" : (: look_dui :),]));
        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_clean_up", 0);
        setup();
//      replace_program(ROOM);
}

void init()
{
        object me;
        me=this_player();

        if( query("gender", me) != "女性" )
        {
                message_vision("$N只覺暗香撲面，眼前一陣暈眩，恍惚間一女子云袖輕舒，你就...\n",me);
                me->move(__DIR__"hsqtan2.c");
        }
}

string look_dui()
{
        return
        "\n"
        "    ※※※※※※※※※※※※※※※※※※※※\n"
        "    ※※※※※※※　　　　　　※※※※※※※\n"
        "    ※※※※※※※　山　　水　※※※※※※※\n"
        "    ※※※※※※※　　　　　　※※※※※※※\n"
        "    ※※※※※※※  色    光　※※※※※※※\n"
        "    ※※※※※※※　　　　　　※※※※※※※\n"
        "    ※※※※※※※  空    斂　※※※※※※※\n"
        "    ※※※※※※※　　　　　　※※※※※※※\n"
        "    ※※※※※※※  蒙    灩　※※※※※※※\n"
        "    ※※※※※※※　　　　　　※※※※※※※\n"
        "    ※※※※※※※　雨　  晴  ※※※※※※※\n"
        "    ※※※※※※※　          ※※※※※※※\n"
        "    ※※※※※※※　亦    方  ※※※※※※※\n"
        "    ※※※※※※※            ※※※※※※※\n"
        "    ※※※※※※※  奇 　 好　※※※※※※※\n"
        "    ※※※※※※※            ※※※※※※※\n"
        "    ※※※※※※※※※※※※※※※※※※※※\n";
}