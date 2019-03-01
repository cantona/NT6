//ROOM: /d/yanziwu/muti.c

inherit ROOM;

void create()
{
        set("short", "木梯");
        set("long", @LONG
這是一座鬆樹枝架成的木梯，垂下來通往水面。忽聽得旁邊柳枝
上一只小鳥 "莎莎都莎，莎莎都莎" 的叫了起來，把你嚇了一跳。南
邊通向船塢。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
            "eastup"  : __DIR__"qinyun",
            "southup" : __DIR__"bozhou",
        ]));
        setup();
        replace_program(ROOM);
}