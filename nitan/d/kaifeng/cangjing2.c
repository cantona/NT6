inherit ROOM;

void create()
{
        set("short", "藏經樓二層");
        set("long", @LONG
小樓的四個角落中放着石灰包，用來吸收空氣中的水份隔段時間，
寺廟中的和尚會把收藏在盒中的佛經放到外面去曬以防日久被蟲子蛀
了，用來晾曬佛經的石頭就稱為曬經石，據説有佛力。
LONG );
        set("objects", ([
                  __DIR__"npc/obj/jing4" : 1,
                  __DIR__"npc/obj/jing3" : 1,
                  __DIR__"npc/obj/jing2" : 1,
                  __DIR__"npc/obj/jing1" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "down" : __DIR__"cangjing",
        ]));

	set("coor/x", -5030);
	set("coor/y", 2220);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}