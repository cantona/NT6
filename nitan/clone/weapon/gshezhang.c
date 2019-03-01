// Code of ShenZhou
// guaishezhang.c
// sdong, 11/20/98

#include <weapon.h>
#include <ansi.h>

inherit STAFF;

string long_desc();

void create()
{
        set_name(HIB"怪蛇杖"NOR, ({ "guai shezhang", "staff", "shezhang" }));
        set_weight(4000);
        set("unit", "根");
        set("long", (: long_desc :));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", (: long_desc :));
        }
                set("value", 450);
                set("material", "steel");
                set("snake_type","怪蛇");
//***** ADDED BY SCATTER *****
                                set("wposition", "/clone/weapon/gshezhang.c");
//***** END OF ADDING *****
                set("wield_msg", HIW"$N抽出一根$n"+HIW"握在手中，杖端的蛇頭呲呲做響，讓人不寒而栗。\n"NOR);
                set("unwield_msg", "$N將手中的$n放了下來。\n");
                init_staff(35);
                setup();
}
string long_desc()
{
                  string desc ;
                  object staff = this_object();

                  desc = HIB"一根彎彎曲曲的黑色粗杖，似是鋼鐵所制，杖頭鑄著個裂口而笑的人頭，人頭口中露出尖利雪白的牙齒，\n模樣甚是猙獰詭異，\n"NOR;

                  if( query("snake", staff) == 1)desc+=HIW"杖上盤著一條銀鱗閃閃的小蛇，不住的蜿蜒上下。\n"NOR;
                  else if( query("snake", staff) == 2)desc+=HIW"杖上盤著兩條銀鱗閃閃的小蛇，不住的蜿蜒上下。\n"NOR;
                  
                  return desc;
}

void init()
{
                  add_action("convert","convert");
}

int convert(string arg)
{
                  object me = this_player();
                  object ob;

                  if (arg!="shezhang" && arg!="staff" && arg!="zhang") return 0;
                  if( query("family/family_name", me) != "白駝山" )
                                         return notify_fail("你不能化杖為蛇。\n");
                  if( query("jing", me)<100 )
                                         return notify_fail("你的精力不夠。\n");

        if (!present("guai shezhang", me))
                return notify_fail("你身上沒有怪蛇杖。\n");

                  if (random(me->query_skill("training",1)) <20) {
                          message_vision("$N手握蛇杖手舞足蹈，好像發瘋一般。\n"
                                         ,me);
                          me->receive_damage("jing", 95);
                          return 1;
                  }

                 if(query("snake") <1)return notify_fail("蛇杖上沒有蛇。\n");

                  message_vision("$N手握蛇杖手舞足蹈，猛地一摔，蛇杖上的毒蛇似箭一般飛了出來。\n",
                                         me,);

                  //seteuid(ROOT_UID);
                  set_default_object(__FILE__);
                  ob = new("/d/xingxiu/npc/guaishe.c");
                  ob->move(environment(me));
                  ob->set_owner(me);
        set("food", 250, ob);

                  addn("snake",-1);

                  return 1;
}

