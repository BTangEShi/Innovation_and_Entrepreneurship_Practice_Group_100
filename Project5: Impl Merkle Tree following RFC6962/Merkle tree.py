import hashlib
import random
import string
# 计算数据块的哈希值
def calculate_hash(data):
    return hashlib.sha256(data.encode()).hexdigest()

# 构建梅克尔树
def build_merkle_tree(leaves):
    if len(leaves) == 1:
        return leaves[0]
    
    nodes = []
    for i in range(0, len(leaves), 2):
        left = leaves[i]
        right = leaves[i+1] if i+1 < len(leaves) else left
        combined_hash = calculate_hash(left + right)
        nodes.append(combined_hash)
    
    return build_merkle_tree(nodes)

# 构建包含证明
def inclusion_proof(merkle_tree, leaf_index):
    proof = []
    current_index = leaf_index
    for level in range(len(merkle_tree)):
        sibling_index = current_index + 1 if current_index % 2 == 0 else current_index - 1
        sibling_node = merkle_tree[level][sibling_index] if sibling_index < len(merkle_tree[level]) else ''
        proof.append(sibling_node)
        current_index //= 2
    
    return proof

# 构建排除证明
def exclusion_proof(merkle_tree, leaf_index):
    proof = []
    current_index = leaf_index
    for level in range(len(merkle_tree)):
        sibling_index = current_index + 1 if current_index % 2 == 0 else current_index - 1
        sibling_node = merkle_tree[level][sibling_index] if sibling_index < len(merkle_tree[level]) else ''
        proof.append(sibling_node)
        current_index //= 2
    
    return proof

# 示例数据块
def generate_random_string(length):
    letters = string.ascii_letters
    return ''.join(random.choice(letters) for i in range(length))

# 生成一百个随机字符串，每个字符串长度为10
data_blocks = [generate_random_string(10) for _ in range(100000)]
##data_blocks=["hello","world","tang","shi"]
# 计算叶节点的哈希值
merkle_tree = [list(map(calculate_hash, data_blocks))]

# 构建梅克尔树
while len(merkle_tree[-1]) > 1:
    current_level = merkle_tree[-1]
    next_level = []
    for i in range(0, len(current_level), 2):
        left = current_level[i]
        right = current_level[i+1] if i+1 < len(current_level) else left
        combined_hash = calculate_hash(left + right)
        next_level.append(combined_hash)
    merkle_tree.append(next_level)

# 选择一个要验证的叶节点索引
verification_index = 1

# 构建包含证明和排除证明
inclusion_proof = inclusion_proof(merkle_tree, verification_index)
exclusion_proof = exclusion_proof(merkle_tree, verification_index)

# 输出结果
##print("Merkle Tree:")
##for level in merkle_tree:
    ##print(level)

print("\nVerification Index:", verification_index)
print("Inclusion Proof:", inclusion_proof)
print("Exclusion Proof:", exclusion_proof)
