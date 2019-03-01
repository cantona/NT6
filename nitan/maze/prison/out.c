inherit ROOM; 

void create() 
{ 
        set("short", "天牢出口"); 
        set("long", @LONG 
這裡黑沉沉的，即無一絲光亮，也無半分聲息。黑暗中依稀可以
看到身邊似乎有幾個人影，看到你轉過頭去，他們立刻屏住呼吸，緊
張地瞪著你。四壁摸上去冰涼，且極硬，似乎都是鋼鐵鑄成。腳邊有
一堆東西踢上去克剌剌地散了開來，細看卻是一具白得發亮的枯骨。
LONG
); 
                        
        set("outdoors", "necropolis"); 
        set("virtual_room", 1);
        set("no_magic", 1);
        set("exits", ([ /* sizeof() == 3 */ 
                "north":__DIR__"maze/exit",
                "out"  : "/d/beijing/hg_w",
        ])); 
                        
        setup();

} 
int valid_leave(object me, string dir)
{
        object *inv, obj;
        if (dir == "out")
        {
                tell_object(me, "check!\n");
                inv = all_inventory(me);
                if (inv && sizeof(inv)>0)
                        foreach(obj in inv) {
                                if (obj && obj->query("maze_item"))
                                        destruct(obj);
                        }
        }
        return 1;
}

