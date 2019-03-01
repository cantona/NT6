inherit ROOM;
void create()
{
        set("short", "石屋");
        set("long",
"走著走著，秘道中忽然亮起了燈光。前面巖壁，已被鑿成石燈的模樣\n"
"，燈蕊竟有十余條之多，互相連接。石室中一直是陰濕而黝暗，左面一張\n"
"石床，右面一張石桌，幾張石凳。\n"
);
        set("no_magic", "1");
        set("exits",([
                "out" :__DIR__"shishi",
        ]) );
        set("objects",([
                __DIR__"npc/kuangren1" : 1,
        ]) );
        setup();
}
