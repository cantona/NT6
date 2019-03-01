inherit ROOM;

void create()
{
        set("short", "大漠風光");
        set("long", @LONG
地勢到這是豁然開朗，你的西邊是一望無際的沙漠。狂風
在呼哮，漫天黃沙在飛舞，飛沙滾滾。沙礫打在你的身上，就
像是蒼穹怒投下的冰雹。冥冥中仿佛已有種邪惡的力量，任何
人隨時都有可能突然像野狗般死在沙礫上。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                "west" : __DIR__"shamo3",
                "east" : __DIR__"shamo1",
        ]));
        setup();
        replace_program(ROOM);
}