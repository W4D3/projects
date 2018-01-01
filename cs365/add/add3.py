def add(nums, sum):
    if len(nums) == 0: return sum
    else:
        return add(nums[1:], sum + nums[0])

print add([3,4,6,9,12], 0)
