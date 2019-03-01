// system.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

string fs(int supplied);
string fc(int cost);

int main(object me, string arg)
{
        string msg;
        mapping cm;

        cm = COMBAT_D->query_entire_dbase();
        msg = "系統現在的配置：\n";
        if (! mapp(cm))
                msg += "不祥。\n\n";
        else
                msg += "PK 人數限制：每天不超過 " HIR +
                       cm["pk_perday"] + NOR " 人，每人不超過 "
                       HIR + cm["pk_perman"] + NOR + " 次。\n\n";

        cm = CPU_D->query_entire_dbase();
        msg += "最近一段時間系統使用CPU的情況統計：\n";
        msg += "系統提供CPU資源的滿足度：" + fs(cm["last_0"]["supplied"]) +
              "  遊戲對CPU的佔用率：" + fc(cm["last_0"]["cost"]) + "。\n";

        msg += sprintf("前一些時間CPU的滿足度和佔用率：%s/%s  %s/%s  %s/%s  %s/%s。\n",
                       fs(cm["last_1"]["supplied"]), fc(cm["last_1"]["cost"]),
                       fs(cm["last_2"]["supplied"]), fc(cm["last_2"]["cost"]),
                       fs(cm["last_3"]["supplied"]), fc(cm["last_3"]["cost"]),
                       fs(cm["last_4"]["supplied"]), fc(cm["last_4"]["cost"]));
        write(msg);
        return 1;
}

string fs(int supplied)
{
        if (supplied <= 70)
                return sprintf(RED "%d%%" NOR, supplied);
        else
        if (supplied <= 90)
                return sprintf(HIR "%d%%" NOR, supplied);

        return sprintf(WHT "%d%%" NOR, supplied);
}

string fc(int cost)
{
        if (cost < 0) cost = 0;
        if (cost >= 90)
                return sprintf(RED "%d%%" NOR, cost);
        else
        if (cost >= 70)
                return sprintf(HIR "%d%%" NOR, cost);

        return sprintf(WHT "%d%%" NOR, cost);
}


int help(object me)
{
        write(@HELP
指令格式 : system [-ui] [+|- <門派> <點數>]
 
這個指令可以顯示出目前遊戲的通用配置和使用系統資源的狀況。使
用 ui 參數可以查閱目前 MUD 設計者對于的門派的更新優先級別。
 
HELP );
        return 1;
}