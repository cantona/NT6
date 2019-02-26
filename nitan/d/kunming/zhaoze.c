inherit ROOM;

void create()
{
        set("short", "沼澤邊緣");
        set("long", @LONG
這裏烏雲密佈，天色極暗。再往前走就是武林中有名的死域 
－－火沼澤。那裏不但荊棘密佈，猛獸出沒，還有能至人於死地 
在一瞬間隨時噴射的毒火泉。這有原始森林入口(Forest door)。
LONG
        );
        set("item_desc", ([
                "door" : "從這個入口可以進入原始森林迷宮副本。(enter door)\n",
                "Forest door" : "從這個入口可以進入原始森林迷宮副本。(enter door)\n",
                "forest door" : "從這個入口可以進入原始森林迷宮副本。(enter door)\n",
        ]));

        set("exits",([
                "east" : __DIR__"yunnan1",
        ]));
        set("objects", ([ 
                "maze/forest/forest_door" : 1,
        ]));
	set("coor/x", -16770);
	set("coor/y", -7160);
	set("coor/z", 0);
	setup();
        // replace_program(ROOM);
}
