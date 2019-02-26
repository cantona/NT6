inherit ROOM;

void create()
{
        set("short", "風火居");
        set("long", @LONG
這裏是凌霄雙傑之一—封萬里的房間。房間混亂不堪，到處
都是刀劍砍鑿的痕跡，好像被誰在這發泄過怒火似的。一名手持
長劍，少了一臂，而偏又面帶怒色的中年男子，站在屋中，凝望
窗外，正牙關緊咬,似有無限恨事。
LONG);
        set("exits", ([
                    "west" : __DIR__"houyuan2", 
        ]));
        set("objects", ([  
                __DIR__"npc/feng" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
