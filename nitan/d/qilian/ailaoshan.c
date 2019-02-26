// Room: /d/qilian/ailaoshan.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "哀牢山");
        set("long", @LONG
此山毫無生氣，寸草不生，一但踏入山中, 頓感一股莫可名狀的怪
捩之息，傳説中的神仙刑天想刺殺天帝，沒有成功，天帝砍了他的頭。
刑天以臍為嘴，雙乳為目，繼續和天帝作戰，失敗後被困於此山。
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "southeast" : __DIR__"tieshishan",
                "southwest" : __DIR__"zibaipo",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -13500);
        set("coor/y", 3500);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}