// /d/xiakedao/yongdao3.c 俠客島 甬道3

inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
這裏往來者甚多，多數是急匆匆武林人物，亦有不少青衣弟子。
許多人都手持食物邊走邊吃，惟恐耽誤了時間。幾個衣衫襤褸的乞丐
便在牆邊鼾然入睡。一個小僮踮起腳尖，正在添加燈油。
LONG );
        set("exits", ([
                "south" : __DIR__"shimen",
                "north" : __DIR__"dating",
        ]));
        set("objects", ([
                __DIR__"npc/tongzi" : 1,
        ]));
        set("coor/x", -3080);
        set("coor/y", -22120);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}