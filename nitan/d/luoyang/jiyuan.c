inherit ROOM;

void create()
{
        set("short", "春月樓");
        set("long", @LONG
此樓雖不在京城，但卻是中原最有名的青樓。這裡有最貴的酒，最華
麗的擺設，也有最優質的服務，更有最貴的女人，最風騷且最有味的女人。
當然，前提是你要有足夠的錢！樓內到處張燈結彩，香氣撲鼻。老鴇正忙
的不亦樂乎，幾名打扮得妖裡妖氣的女人分站兩旁對你發出媚笑。從樓上
傳來了陣陣打情罵俏的聲音。朱紅大門上高懸一塊御賜金匾：春色滿園。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "up" : __DIR__"jiyuan2",
                  "west" : __DIR__"sroad5",
        ]));
        set("objects", ([
                __DIR__"npc/laobao" : 1,
                "/d/beijing/npc/jinv" : 1,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2130);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}