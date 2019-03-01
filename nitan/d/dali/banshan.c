//Room: /d/dali/banshan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","半山竹林");
        set("long",@LONG
一大片茂密的成年竹林生長在半山腰的緩坡上。竹子對大理地區
各民族來說是，既是重要的建築材料，也是日常生活用品的原材料。
山下的村莊裡的擺夷人經常上山來採伐竹子。北面山上有溪流下，到
這裡水流已經頗大，山民經常把砍伐下的竹子丟在溪中，任其順水飄
流，到村子附近的溪水裡再撈起來。
LONG);
        set("objects", ([
           __DIR__"npc/kanzhuren": 2,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "northup"  : __DIR__"shanjian",
            "east"     : __DIR__"buxiongbu",
        ]));
	set("coor/x", -19030);
	set("coor/y", -6910);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}