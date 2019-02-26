inherit ROOM;

void create()
{
        set("short", "書房");
        set("long", @LONG
這是一間乾乾淨淨的書房。當中一個大檀木桌，桌上放着
不少書籍。靠牆的地方還有一個書架，架上滿滿的全是各種封
裝的書。其中不少書看上去古意盎然，顯然年代已久。
LONG);
        set("exits", ([
                "down" : __DIR__"daojufang",
        ]));
        set("objects", ([
                "/clone/book/yijing" + random(4) : 1,
                "/clone/book/yijing" + random(4) : 1,
                "/clone/book/jiuzhang" : 1,
                CLASS_D("taohua") + "/qu": 1,
        ]) );
        setup();
        replace_program(ROOM);
}