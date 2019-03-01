inherit ROOM;

void create()
{
        set("short", "沙礫小徑");
        set("long", @LONG
這是一個無邊的沙礫地，山勢到了這裡突然間變的無影無
蹤。地氣極幹燥，連風都是暖的。地上的石礫發出一種暗紅的
顏色，就象是被鮮血染紅的一樣。一條布滿車痕的小徑向西方
和東方伸展。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                  "west" : __DIR__"shamo2",
                  "eastup" : __DIR__"caoyuan7",
        ]));
        setup();
        replace_program(ROOM);
}