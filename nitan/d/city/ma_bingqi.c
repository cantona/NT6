inherit ROOM;

void create()
{
        set("short", "兵器庫");
        set("long", @LONG
這裡是馬莊內存放兵器的重地，房裡擺滿了兵器架十八般
兵刃樣樣齊全。架子旁邊掛著數十副閃閃發光的盔甲腰帶和戰
靴等物。一位丐幫五袋弟子正閉目養神，看守著這裡。
LONG);
        set("exits", ([
                "east"  : __DIR__"ma_lianwu1",
        ]));
        set("objects", ([
                "/d/gaibang/npc/5dai" : 1,
                "/d/gaibang/npc/obj/staff" : 3,
                "/clone/weapon/changjian" : 2,
                "/clone/weapon/gangdao" : 2,
        ]));
        set("region", "yangzhou");
        set("no_clean_up", 0);
	set("coor/x", 20);
	set("coor/y", -70);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}