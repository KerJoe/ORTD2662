import math

#  a      ; a_min < a < a_max ∈ N
# --- = p ; b_min < b < b_max ∈ N
#  b      ; p ∈ R

p = math.pi

a = None
a_min = 0
a_max = 255

b = None
b_min = 0
b_max = 255

#  bound_less_a     a     bound_more_a
# -------------- < --- < --------------
#  bound_less_b     b     bound_more_b

bound_less_a = None
bound_less_b = None

bound_more_a = None
bound_more_b = None


##


bound_less_a = math.floor(p)
bound_less_b = 1

bound_more_a = math.ceil(p)
bound_more_b = 1

while(1):
    # Get Mediant
    med_a = bound_less_a + bound_more_a
    med_b = bound_less_b + bound_more_b
    # Stop condition
    if (med_a > a_max) or (med_b > b_max):
        # Return closest
        if (abs(bound_less_a/bound_less_b - p) < abs(bound_more_a/bound_more_b - p)): # bound_less is closest
            a = bound_less_a
            b = bound_less_b
            break
        else: # bound_more is closest
            a = bound_more_a
            b = bound_more_b
            break
    # Replace worst bound with median
    if (med_a/med_b < p):
        bound_less_a = med_a
        bound_less_b = med_b
    else:
        bound_more_a = med_a
        bound_more_b = med_b

print(f"Answer: {a}/{b}={a/b}; Error={(p-(a/b))/p*100}%")