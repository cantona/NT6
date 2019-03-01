inherit ROOM;

void create()
{
        set("short", "冰洞");
        set("long", @LONG 
這裡又是一個冰洞，但從這裡往上望，居然可以透過冰壁看
到外面的萬裡群山。原來這外面的牆壁是懸崖上的冰層，月光射
進冰洞，照得滿洞生輝，銀光閃閃，讓人想起‘冰簟銀床夢不成，
碧天如水夜雲輕’的意境。
LONG);
        set("exits", ([
                    "enter" : __DIR__"wave", 
                    "east"  : __DIR__"wave1", 
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
