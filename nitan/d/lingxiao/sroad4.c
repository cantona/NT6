#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "天風川");
        set("long", @LONG
你正站在一塊晶瑩剔透的萬年冰川之上，只覺腳部不斷傳來
一陣透骨的冰涼。雪山上北風怒號，萬裡愁雲淡霧籠罩雪域，四
周一片蒼茫，已經看不見半點生命跡象了。片片雪花從空中鵝毛
般飛撒而下。足底溜滑，道路更是難於辨認。可謂“雪道難，難
于上青天”。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "southdown"  : __DIR__"shiya",
                    "northup"  : __DIR__"sroad5",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}