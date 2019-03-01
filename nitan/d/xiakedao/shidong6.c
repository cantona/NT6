// /d/xiakedao/shidong6.c 俠客島 石洞

inherit ROOM;

void create()
{
        set("short", "石洞");
        set("long", @LONG
這是一個石洞，略顯狹窄，僅容兩人並肩而過。頂壁也甚是低
矮，伸手便可觸及。油燈晃動，在身後拉出長長的陰影。腳步踢嗒
石洞彼端響起陣陣回聲，感覺有些異樣。
LONG );
        set("exits", ([
                "south" : __DIR__"shidong7",
                "north" : __DIR__"shidong1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3100);
        set("coor/y", -22090);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}