#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        string tmp;
        int no;
        set_name(CYN "玄鐵劍" NOR,({"xuantie jian","xuantie","jian"}));
        set_weight(140000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "重劍無鋒，大巧不工。這柄劍是天外玄鐵所鑄，無刃無鋒，拙鈍無比。然而，裂金玉如破腐土，無堅不摧。神雕俠楊過昔年憑它名揚天下。\n");
                set("material", "steel");
                set("no_drop", "如此寶貴的武器再世難求啊。\n");
                set("no_give", "送人？虧你想的出來！\n");
                set("no_put", "珍惜它吧。\n"); 
                set("no_sell", "賣？這樣的神兵用來賣？你是不是快餓死了？\n");   
                set("wield_msg", CYN "$N緩緩從背後拔出玄鐵劍，天地間頓時一片陰霾，隱隱有雷聲滾動。\n" NOR);
                set("unwield_msg", CYN "$N神色凝重，將玄鐵劍納入背後的布包中，霎時間風雷隱隱。\n" NOR);
       }
// modified by chacha
       init_sword(70);
       setup();
// following 2 lines was added by chacha
       sscanf(file_name(),"%s#%d",tmp,no);
       if(no>0) destruct(this_object()); 
}

void init()
{
        add_action("do_get","get");
// modified by chacha
        set("weapon_prop/damage",query("max_neili", this_player())/2);
}

int do_get(string arg)
{
        object me,ob;
        me=this_player();
        ob=this_object(); 

    if( !arg ) return notify_fail("你要撿起什麼東西？\n");
        if (arg=="xuantie jian" || arg=="xuantie" || arg=="jian" ) 
         {
       if( query("str", me)<31 )
        return notify_fail("你臂力不足，拿不動玄鐵劍。\n");
        else
        write("好一把絕世的名劍！\n");
        ob->move(me);
        return 1;
         }
}

void owner_is_killed()
{
       destruct(this_object());
}
