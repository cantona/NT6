inherit ROOM;

void create()
{
        set("short", "龍門客棧");
        set("long", @LONG
小酒家幾乎從不打烊，酒舖看起來不差，老板娘長得很不
錯，但不知為什麼，裡邊冷冷清清，看不見一個客人。屋子裡
布置得精雅而別致，每一樣東西都是精心挑選的，正好擺在最
恰當的地方，廳當中供著一個手捧金元寶的財神爺，上面還貼
著張鬥大的紅“喜”字，無論誰走進這裡，都可以看得出這地
方的主人，一定是整天在做著發財夢的窮小子。
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