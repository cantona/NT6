inherit ROOM;

void create()
{
        set("short", "大雪山口");
        set("long", @LONG
這裏已經到了藏邊，大雪山的山口。大雪山又叫岷山，位於川藏
之間，由於山勢高峻，山頂終年不化積雪故而得名。四下毫無人跡，
只有幾隻禿鷹在高處盤旋，俯視着茫茫雪山。
LONG );
        set("exits", ([
                "eastdown"  : __DIR__"sroad3",
                "westup"    : __DIR__"sroad5",
        ]));
        set("objects", ([
                "/clone/quarry/ying" : 2,
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}