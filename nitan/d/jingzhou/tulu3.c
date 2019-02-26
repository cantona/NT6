//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "黃土路");
        set("long", @LONG
這是一條黃土路，通往深山的小山村。兩邊是沒膝的長草，路邊林
木漸行漸密。山裏風光，就是清清流水畔的裊裊白煙，西邊看去，好像
就要到了。一對黃黑相間的大蝴蝶飛在草叢中，一會兒飛到東，一會兒
飛到西，但兩隻蝴蝶始終不分開。湘西一帶的人管這種彩色大蝴蝶叫“
梁山伯，祝英台”。這種蝴蝶定是雌雄一對，雙宿雙飛。
LONG );
        set("exits", ([
                "east"     : __DIR__"tulu2",
                "westup"   : __DIR__"tiandi",
        ]));
        set("outdoors", "jingzhou");
        set("no_clean_up", 0);
        set("coor/x", -7110);
	set("coor/y", -2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}