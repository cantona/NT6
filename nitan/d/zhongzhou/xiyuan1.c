inherit ROOM;

void create()
{
        set("short", "演出大廳");
        set("long", @LONG
這裏就是大廳，台上正唱着戲呢，你可以坐下來叫上一壺
茶，好好的做一次票友。台上那位演員雖不是名角，唱起戲來
倒也是有板有眼，讓人心情一暢，偶然的不快頓時煙消雲散。
LONG);

        set("outdoors", "zhongzhou");

        set("exits", ([
                "east" : __DIR__"xiyuan",
                "west" : __DIR__"huazhuang",    
        ]));

        set("objects",([
                "/d/beijing/npc/guanzhong" : 2,
        ]));

        set("coor/x", -9060);
	set("coor/y", -980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}