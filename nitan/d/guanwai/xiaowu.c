// /guanwai/xiaowu.c

inherit ROOM;

void create()
{
    set("short", "小茅屋");
    set("long", @LONG
這是一座用長白山松木壘成的小屋，屋內打掃的很乾淨。剝離的
牆壁上掛滿了獸皮和雪橇，一張小小的桌旁坐着一個虯髯大漢。北面
看來一扇小門，後面似乎別有洞天。
LONG );
    set("exits", ([
        "south" : __DIR__"xiaoyuan",
        "north" : __DIR__"houyuan",
    ]));
    set("objects", ([
        CLASS_D("hu") + "/hufei" : 1,
                CLASS_D("hu")+"/first" :1,
    ]));
    set("valid_startroom", 1);
    setup();
    "/clone/board/hu_b"->foo();

}
