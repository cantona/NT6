// tai.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",CYN "望鄉台" NOR);
        set("long", 
"這是鬼魂與"+RED "前世" NOR+"告別的最後之所了。眼前是一個高高的"+CYN "石台" NOR+"，四面
凌空，皆是濃霧籠罩一般，如夢似幻，"+HIW "腳下" NOR+"似有萬丈"+BLU "深淵" NOR+"，遠處是曾經
相識的"+HIR "家鄉故土" NOR+"，極目望去，隱隱可見生前之地，親朋好友故土舊屋，
皆"HIG"歷歷如在"NOR"，然虛無縹緲，可望而不可及........\n"
BLU "        望著所有熟悉的一切，你的記憶似乎又被喚醒了，不禁悲\n"
"    從衷來，戀戀不舍.................\n\n" NOR
);
        set("no_fight", 1);
        set("exits", ([ 
                "west" : __DIR__"dadian",
        ]));
        set("no_clean_up", 0);
        setup();
}
void init()
{
        object ob;
        if( interactive(ob = this_player())  )
        {
                remove_call_out("do_string");
                call_out("do_string",20,ob);
        }
}
int do_string(object ob)
{
        if( !ob || environment(ob) != this_object() ) return 0;
        write(BLU "    一個聲音在你耳邊說道：“汝已身入冥府，該當在此于前世一刀兩斷，\n速速去登西方極樂世界為妙，"+RED "切不可再縱身于塵世情色之中......\n\n" NOR);
        ob->unconcious();
        return 1;
}