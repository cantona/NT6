//room: neitang.c
inherit ROOM;

void create()
{
        set("short","內堂");
        set("long", @LONG
這是一間雅致的內堂，布置簡單而典雅。裡面站著個一身淡綠的
女郎，向著你似笑非笑。似乎是江南靈秀造了這樣一個小美人。
LONG );
        set("exits",([
            "north" : __DIR__"qinyun",
        ]));
        set("objects",([
             __DIR__"npc/abi" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
