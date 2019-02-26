inherit ROOM;

void create()
{
        set("short", "山洞");
        set("long", @LONG
這是一個小小的山洞，血刀老祖的藏身之地。由於此地比較隱祕，
仇家很難尋到這來。洞底有一張供桌，上面供了什麼東西，你看不清。
壁上畫了一些模糊不清的文字圖案，也不知道是些什麼。
LONG );
        set("exits", ([
                "out" : __DIR__"shandong2",
                "east": __DIR__"xiuxishi",
        ]));
        set("objects", ([
                CLASS_D("xuedao")+"/laozu" : 1,
                CLASS_D("xuedao")+"/first" : 1,
                __DIR__"npc/x_lama" : 2,
        ]));
        set("valid_startroom", 1);
        setup();
        replace_program(ROOM);

        "/clone/board/xuedao_b"->foo();
}
