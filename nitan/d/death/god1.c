// Room: god1

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"天堂"NOR);
        set("long", HIC @LONG
這裡就是天堂。祥雲朵朵，色澤潔白無瑕，慢慢從你眼前飄過，那翠綠色一
片的草地上開滿了色彩各異的鮮花，香氣繚繞不散，聞著看著，你都快要醉了。
遠處一棟潔白的宮殿，巍然聳入雲霄，從那兒傳來陣陣仙樂，音律和祥悅耳，聽
著聽著，你覺得自己的心靈都已得了到凈化，從此脫離了凡塵俗世……。這兒的
一切都令你覺得安然、陶醉、寧靜、和祥……
LONG
NOR   );
        set("no_magic", 1);
        setup();
}

void reset()
{
        ::reset();
        set("exits", ([ /* sizeof() == 2 */
            "up" : __DIR__"god2",
            "down": "/d/city/wumiao",
        ]));
}
