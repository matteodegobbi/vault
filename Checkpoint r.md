
dependencies = [
    "gymnasium>=1.2.3",
    "highway-env>=1.10.2",
    "torch>=2.3",
    "torchvision",
    "torchaudio",
    "tensorboard>=2.20.0",
    "ipykernel>=7.3.0",
]

python3 src/main.py --mode eval --config configs/double_dqn90.json --model-path checkpoints/double_dqn90_5cfdc373c2d8e89e/DQN_ep6000.pth 

