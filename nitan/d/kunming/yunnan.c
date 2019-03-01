inherit ROOM;

void create()
{
        set("short", "紅土路");
        set("long", @LONG
進入雲貴高原，泥土變為了紅色，空氣變得更清新，放眼
看去，只見周圍那綿綿的原始森林不見邊際，你頓時覺得心高
志遠，一股豪起湧了上來，想要做一方大事業。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "southwest" : __DIR__"yunnan1", 
                "north"  : __DIR__"road7",
        ]));
        setup();
        replace_program(ROOM);
}
