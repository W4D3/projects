def add(nums):
    if len(nums) == 1: return nums[0]
    else:
        return nums[0] + add(nums[1:])

print add([3,4,6,9,12])
