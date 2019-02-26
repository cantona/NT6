inherit ROOM;

void create()
{
        set("short", "龍門客棧");
        set("long", @LONG
小酒家幾乎從不打烊，酒鋪看起來不差，老闆娘長得很不
錯，但不知為什麼，裏邊冷冷清清，看不見一個客人。屋子裏
佈置得精雅而別緻，每一樣東西都是精心挑選的，正好擺在最
恰當的地方，廳當中供着一個手捧金元寶的財神爺，上面還貼
着張斗大的紅“喜”字，無論誰走進這裏，都可以看得出這地
方的主人，一定是整天在做着發財夢的窮小子。
LONG);
        set("objects", ([
                  __DIR__"npc/jinxiangyu" : 1,
        ]));
        set("exits", ([
                  "south" : __DIR__"guandao2",
        ]));

        setup();
        replace_program(ROOM);
}