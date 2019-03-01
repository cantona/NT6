inherit ROOM;

void create()
{
        set("short", "落燕廳");
        set("long", @LONG
四小廳借沉魚落燕羞花閉月之典故而起名，此廳內高爽寬敞，窗台明
亮。堂中掛一幅無名小畫，設一張白木臥榻。桌凳之類，色色潔凈。打掃
得地下無纖毫塵垢。堂中花卉無所不有，十分繁茂。真個四時不謝，八節
長春。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"jiyuan2",
        ]));

	set("coor/x", -6990);
	set("coor/y", 2130);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}