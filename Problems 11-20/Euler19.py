import datetime

def is_leap_year(date):
    if date.year % 4 != 0:
        return False
    elif date.year % 100 == 0 and date.year % 400 != 0:
        return False
    else:
        return True

def one_month_timedelta_from(date):
    month = date.month
    if month == 2:
        if is_leap_year(date):
            return datetime.timedelta(days = 29)
        else:
            return datetime.timedelta(days = 28)
    elif month == 4 or month == 6 or month == 9 or month == 11:
        return datetime.timedelta(days = 30)
    else:
        return datetime.timedelta(days = 31)

sundays = 0
date = datetime.date(1901, 1, 1)
while date.year < 2001:
    if date.weekday() == 6:
        sundays += 1
    date += one_month_timedelta_from(date)

print(sundays)
