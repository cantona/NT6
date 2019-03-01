#include <weapon.h>
#include <ansi.h>

#define RAGE "「" HIR "□拉□之怒" NOR "」"
#define RAGEC "「" HIR "□拉□之怒" NOR

#define SHIELD "「" HIB "洛山□高等□盾" NOR "」"
#define SHIELDC "「" HIB "洛山□高等□盾" NOR

string look_sword();
void remove_effect(object me, int amount);

inherit SWORD;

void create()
{
        set_name(HIY "神□□□" NOR, ({ "long sword", "sword" }));
        set_weight(1000);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "柄");
                set("no_sell", 1);
                set("long", (: look_sword :));
                set("value", 2000000);
                set("no_sell", "Oh！My god！");
                set("material", "???");
                set("stable", 100);
        }
        init_sword(500);
        setup();
}

void init()
{
        add_action("do_cast", "cast");
}

string look_sword()
{
        return HIY
        "\n"
        "神□□□+5：「" HIR "□神的喧□" HIY "」\n\n"
        "□把□□除了柄端由白□所□外，整□□身漆黑，□□□刃，便似薄\n"
        "□片般。但是□你的指尖□碰到□身□，能感到一□刺骨的冰□，□\n"
        "□甚至□□□它是有心跳的。□神的喧□□造於1039 DR ，□造者是\n"
        "□□吉德的一位高□牧□，□□□□吉德受到半□人的□剿□□三年\n"
        "之久，運□物□的道路被切□，□士和人□由於□期得不到□□，大\n"
        "都士□低落，而斯洛塔神□的牧□在□役中□□任了救援和□□的工\n"
        "作，同□牧□□也在不停地向□神祈禱，以求保佑平安。□管人□虔\n"
        "誠的信奉著□神，等待上天□□□助，但□□吉德仍於1042 DR 被半\n"
        "□人攻□，同□斯洛塔神□成了一片□墟，□把□也不知所□。\n\n"
        "黑□克﹒□□斯是一位□落的□武士，在撒丁□城素以冷酷和勇猛著\n"
        "□，人□□他是「□刃手」，□不知他的很大一部分能力是□自於他\n"
        "的配□。一次在撒丁□城的酒吧中，一位喝醉的矮人□賊不□他的□\n"
        "□，向他□出了挑□。□然黑□克﹒□□斯英勇善□，也手刃了□位\n"
        "狂妄的矮人□賊，但他仍然□不□前□□忙的大群□武士集□的雇傭\n"
        "兵，被分成了七□。而□把□也被傭兵□□□作□利品取走。\n\n" NOR
        "□□□料：\n"
        "□害力：" WHT "1d10+5，□善良或是邪□□□的□人□□得+10改善\n" NOR
        "零□命中值：" WHT "□得+7改善\n" NOR
        "□害□型：" WHT "□砍\n" NOR
        "抗力加值：\n" WHT
        "  +15%魔法抗力\n"
        "  +50%寒冷抗力\n"
        "  □□吐攻□的豁免率□定+10有利\n" NOR
        "特殊功能：\n" WHT
        "  每天施展一次□拉□之怒\n"
        "  每天施展□次洛山□高等□盾\n"
        "  每天施展三次英雄□概\n"
        "  持用者□死亡一指/律令：死亡/狂暴魅惑/恐□之袍/□助法印免疫\n"
        "  □中目□後有15%□□□目□震昏，□□10□\n"
        "  □中目□後有50%□□以持用者□中心□出一□3d6的火球\n" NOR
        "重量：" WHT "10\n" NOR
        "使用速度：" WHT "1\n" NOR
        "武器特□□□：" WHT "大型□\n" NOR
        "□□：" WHT "□手持用\n" NOR
        "□法使用的□□：\n" WHT
        "  德□伊\n"
        "  牧□\n"
        "  法□\n" NOR
        "唯一能使用的人物：\n" WHT
        "  混□□□的人物\n" NOR;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        n = 3 + random(16);

        if (random(100) < 15 && living(victim))
        {
                victim->unconcious();
                return HIR "霎□□只□$N" HIY "神□□□" HIR"□芒暴"
                       "□，$n" HIR "□□一□昏眩。\n" NOR;
        } else
        if (random(100) < 50)
        {
                victim->receive_wound("qi", n * 100, me);
                victim->receive_wound("jing", n * 50, me);
                return HIR "只□$N" HIY "神□□□" HIR"□尖陡然□射"
                       "出" + chinese_number(n) + "□火球，□□□在"
                       "$n" HIR "全身。\n" NOR;
        }
}

int do_cast(string arg)
{
        object me = this_player(), *obs;
        int n, i, flag, damage;

        if (! arg || arg == "")
                return notify_fail("你要施展什麼法□？\n");

        if (arg != "rage" && arg != "shield")
                return notify_fail("你□法施展此□法□。\n");

        if (arg == "rage")
        {
                me->clean_up_enemy();
                obs = me->query_enemy();

                if (! me->is_fighting())
                        return notify_fail("你只有在□□中才能施展"
                                           RAGE "。\n");

                if (me->is_busy())
                        return notify_fail("你□在正在忙，□有□□"
                                           "施法" RAGE "。\n");

                message_vision(HIW "\n$N" HIW "施法" RAGEC + HIW "」"
                               "，高□念□道：比迪姆﹒□特蒙﹒泰裡"
                               "阿普﹒埃控。\n\n" NOR, me);
                me->start_busy(5);

                for (flag = 0, i = 0; i < sizeof(obs); i++)
                {
                        if (random(10) > 3)
                        {
                                tell_object(obs[i], HIR "你只□眼前光芒"
                                                    "一□，霎□□□□光"
                                                    "□便如□□般刺入□"
                                                    "內，□欲窒息。\n" NOR);

                                damage = 1000 + random(3000);
                                obs[i]->receive_wound("qi", damage);
                                obs[i]->receive_wound("jing", damage / 2, me);

                                message("vision", HIY + obs[i]->name() +
                                                  HIY "只□眼前光芒一□"
                                                  "，霎□□□□光□便如"
                                                  "□□般刺入□內，□欲"
                                                  "窒息。\n\n" NOR,
                                                  environment(me),
                                                  ({ obs[i] }));
                                flag = 1;
                        } else
                        {
                                tell_object(obs[i], HIC "你法□豁免率□定"
                                                    "成功，避□了" RAGEC +
                                                    HIC "」的攻□。\n" NOR);
                        }
                }
                if (! flag) 
                        message_vision(HIC "然而□有任何人受到$N" RAGEC +
                                       HIC "」的影響。\n" NOR, me, 0, obs);
                return 1;
        }

        if (arg == "shield")
        {
                if( query_temp("shieldc", me) )
                        return notify_fail("你已□施展了" SHIELD "。\n");

                n = 500;

                message_vision(HIW "\n$N" HIW "施法" SHIELDC + HIW "」"
                               "，高□念□道：□帝斯﹒索利﹒洛哈吾吉特"
                               "﹒莫拉□拉。\n\n" NOR, me);

                addn_temp("apply/armor", n, me);
                set_temp("shieldc", 1, me);

                me->start_call_out((: call_other, __FILE__, "remove_effect",
                                      me, n :), n);

                return 1;
        }
}

void remove_effect(object me, int n)
{
        if( query_temp("shieldc", me) )
               {
                       addn_temp("apply/armor", -n, me);
                       delete_temp("shieldc", me);
                       tell_object(me, "你的" SHIELD "施展完□。\n");
               }
}