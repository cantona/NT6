// Room: /d/playtown/miao.c
// Build 199.12.10 bmw

inherit ROOM;

void create()
{
        set("short", "關公廟");
        set("long",
"你步入關公廟，一眼便看見一尊長髯棗面的關公像，八尺高的身軀顯\n"
"得威嚴無比。天下百姓為了紀念這位功高蓋主的關將，許多地方都有紀念\n"
"他的廟宇，聽説百試百靈。只見關公像前是一張香案，上面有幾柱香冉冉\n"
"飄起。在你的正面前擺着一個蒲團(putuan)，右面有個算命先生閉着眼睛，\n"
"嘴裏不知道在哼着什麼。\n"
);

        set("item_desc",([
                "putuan":"這是一個小蒲團，專供人下跪用。\n",
        ]));
        
        set("exits", ([
                "west"  : __DIR__"road7",
                "east"  : __DIR__"road18",
                "north"  : __DIR__"biwuchang",
                "south"  : __DIR__"liaotianshi",
        ]));
        setup();
        replace_program(ROOM);
}