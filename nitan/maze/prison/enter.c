inherit ROOM; 

void create() 
{ 
        set("short", "天牢入口"); 
        set("long", @LONG 
這裏黑沉沉的，即無一絲光亮，也無半分聲息。黑暗中依稀可以
看到身邊似乎有幾個人影，看到你轉過頭去，他們立刻屏住呼吸，緊
張地瞪着你。四壁摸上去冰涼，且極硬，似乎都是鋼鐵鑄成，只有南
北面各有一道小門，門上開了個巴掌大的洞，象是送飯用的。腳邊有
一堆東西踢上去克剌剌地散了開來，細看卻是一具白得發亮的枯骨。
LONG
); 
                        
        set("outdoors", "prison"); 
        set("virtual_room", 1);
        set("no_death", 1);
        set("no_magic", 1);
        set("exits", ([ /* sizeof() == 3 */ 
                "south" : __DIR__"maze/entry", 
        ])); 
        set("objects",([
                "/maze/prison/npc/taijian" : 1,
        ])); 
        setup();
 
} 

