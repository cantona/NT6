//lhqyuan.c
inherit ROOM;

void create()
{
        set("short", "大院");
        set("long", @LONG
你走進了烈火旗的大院，卻發現這裏人聲鼎沸，烈火教眾有的在
搬火藥，有的在煉石油，真是熱火朝天。院子左首可能是練武場，隱
約傳來打鬥聲；右首是一座大廳，象是烈火旗的議會場所。向上走就
是光明頂明教總舵了。
LONG );
        set("exits", ([
                "west"    : __DIR__"lhqlwch",
                "northup" : __DIR__"lhqhoumen",
                "east"    : __DIR__"lhqdating",
                "out"     : __DIR__"lhqmen",
                "enter"   : __DIR__"huroom",
        ]));
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}