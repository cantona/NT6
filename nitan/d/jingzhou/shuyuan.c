inherit ROOM;

void create()
{
        set("short", "蕭湘書院");
        set("long", @LONG
這裏是書院的講堂，窗明几淨，一塵不染。一位莊重嚴肅的老者
坐在太師椅上講學，那就是當今大儒韓先生了。在他的兩側坐滿了求
學的學生。一張古意盎然的書案放在朱先生的前面，案上擺着幾本翻
開了的線裝書籍。
LONG );
        set("exits", ([
                  "north" : __DIR__"dongdajie1",
                  "south" : __DIR__"shuyuan1",
        ]));
        set("objects", ([
                  __DIR__"npc/xiaoxiang" : 1,
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7090);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}